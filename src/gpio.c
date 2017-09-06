#include "gpio.h"

uint32_t qei_ch_a_history = 0;
uint32_t qei_ch_b_history = 0;

void rotaryEncoderHandler(void);
void switchHandler(void);

void gpioInit() {
    
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // for data-command and reset
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // for leds and switches
    // configure pins for input or output 
    
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, PIN_DC|PIN_RST);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_BLUE|LED_GREEN);

    //First open the lock and select the bits we want to modify in the GPIO commit register.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW_SELECT|SW_BACK);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    GPIOIntDisable(GPIO_PORTF_BASE, SW_SELECT|SW_BACK);
    GPIOIntClear(GPIO_PORTF_BASE, SW_SELECT|SW_BACK);
    GPIOIntRegister(GPIO_PORTF_BASE, switchHandler);
    GPIOIntTypeSet(GPIO_PORTF_BASE, SW_SELECT|SW_BACK, GPIO_RISING_EDGE);
    IntPrioritySet(INT_GPIOF, 190); //important icw. freertos on arm
    GPIOIntEnable(GPIO_PORTF_BASE, SW_SELECT|SW_BACK);


    // PC5 and PC6 are connected to the rotary encoder
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);
    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_INT_PIN_5 | GPIO_PIN_6);
    GPIOIntRegister(GPIO_PORTC_BASE, rotaryEncoderHandler);
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6, GPIO_BOTH_EDGES);
    IntPrioritySet(INT_GPIOC, 190); //important icw. freertos on arm
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);

    // Set all outputs to zero
    GPIOPinWrite(GPIO_PORTE_BASE, PIN_DC|PIN_RST, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE|LED_GREEN, 0);
}

void gpioResetOn(void){
	// Reset is active when low
	GPIOPinWrite(GPIO_PORTE_BASE, PIN_RST, 0);
}

void gpioResetOff(void){
	// reset is not active when high
	GPIOPinWrite(GPIO_PORTE_BASE, PIN_RST, PIN_RST);
}

void gpioCommandMode(void){
	// command mode is active when low
	GPIOPinWrite(GPIO_PORTE_BASE, PIN_DC, 0);	
}

void gpioDataMode(void){
	// data mode is active when high
	GPIOPinWrite(GPIO_PORTE_BASE, PIN_DC, PIN_DC);
}

void gpioLedBlue(bool high) {
    if (high) {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE, LED_BLUE);
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_BLUE, 0);
    }
}

void gpioLedGreen(bool high) {
    if (high) {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, LED_GREEN);
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, 0);
    }
}

void rotaryEncoderHandler(void) {

    // The rotary encoder provides the following signals:
    //        ____      ____      ____
    // a ____|    |____|    |____|    |__ etc.
    //
    //      ____      ____      ____      __
    // b __|    |____|    |____|    |____|    etc.
    //              ^         ^         ^
    // The rotary encoder rests into positions ("clicks") indicated by the "^".
    // Initially, I used the tivaware qei interrupt, but it only interrupts at
    // a direction change, so I would need to poll it for a position change.
    // Then I used an interrupt on the A rising edge, but that gives 
    // false positives as the rotary encoder is very sensitive one way 
    // and not so sensitive the other way.
    // 
    // This implementation uses a handler that handles inrterrupts 
    // - on both rising and falling edges
    // - on both a and b signals.
    // Every interrupt:
    //  1. the history (bits in an uint, most recent is lsb) is left-shifted, making
    //     the lsb "free".
    //  2. the value of both signals is retrieved and stored as the lsb in the history ints.

    // whenever the history is 0110 for a, and 1100 for b, we have a rotation right, from
    // one clicky position, fully to the next clicky position.
    // A shift lift in a similar way.
    // Too old history (5th bit and above) is masked away.

    // This way matches the intuitive clicky feeling most, without being too sensitive, and
    // without being more sensitive in one direction then the other.

    //* We have not woken a task at the start of the ISR. */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Get the interrrupt status.
    uint32_t ui32Status = GPIOIntStatus(GPIO_PORTC_BASE, true);
    // Clear the asserted interrupts.
    GPIOIntClear(GPIO_PORTC_BASE, ui32Status);

    // read both pin 5 and pin 6
    uint32_t read = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);

    // shift history up
    qei_ch_a_history = qei_ch_a_history << 1;
    qei_ch_b_history = qei_ch_b_history << 1;

    qei_ch_a_history |= (uint32_t) (read & GPIO_PIN_5) == GPIO_PIN_5;
    qei_ch_b_history |= (uint32_t) (read & GPIO_PIN_6) == GPIO_PIN_6;

    if ( ((qei_ch_a_history & 0x0000000F) == 12 ) &  //1100 
         ((qei_ch_b_history & 0x0000000F) == 6) ) {  //0110
        // send event to the queue
        // for now: 0 is up, 1 is down, 2 is click.
        if (rxQueue != 0) {
            enum UIEvent event = DOWN;
            xQueueSendFromISR(rxQueue, &event, &xHigherPriorityTaskWoken);
        }
    } 
    else if ( ((qei_ch_a_history & 0x0000000F) == 6 ) &   //0110
              ((qei_ch_b_history & 0x0000000F) == 12) ) { //1100
        if (rxQueue != 0) {
            enum UIEvent event = UP;
            xQueueSendFromISR(rxQueue, &event, &xHigherPriorityTaskWoken);
        }
    }

    /* Now the buffer is empty we can switch context if necessary. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void switchHandler(void) {

    // We have not woken a task at the start of the ISR. 
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Get the interrrupt status.
    uint32_t ui32Status = GPIOIntStatus(GPIO_PORTF_BASE, false);
    
    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & SW_SELECT) {
        enum UIEvent event = SELECT;
        xQueueSendFromISR(rxQueue, &event, &xHigherPriorityTaskWoken);
        // Clear the asserted interrupts.
        GPIOIntClear(GPIO_PORTF_BASE, ui32Status);
    } else if (GPIOIntStatus(GPIO_PORTF_BASE, false) & SW_BACK) {
        enum UIEvent event = BACK;
        xQueueSendFromISR(rxQueue, &event, &xHigherPriorityTaskWoken);
        GPIOIntClear(GPIO_PORTF_BASE, ui32Status);
    } else {
        // we should never be here
        // get stuck in a loop so we can debug
        while(true) {};
    }
    
    
    /* Now the buffer is empty we can switch context if necessary. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}



