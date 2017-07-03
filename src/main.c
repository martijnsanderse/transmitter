/*
 * main.c
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#include "semphr.h"
#include "portmacro.h"


#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"

#define LED1 GPIO_PIN_1
#define LED2 GPIO_PIN_2
//#define PWM_PERIOD 8000 // so pwm at 10kHz if 80Mhz clock.

QueueHandle_t rxQueue;


// task prototypes
    
void blinkRedTask(void *);  // prototype so we can include it in main while the code is underneath


void setupPeripherals(void){
    // enable peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // DIO
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // serial
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // serial
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  // PWM
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); // PWM

    // initialize peripherals
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED1|LED2);
    GPIOPinWrite(GPIO_PORTF_BASE, LED1|LED2, 1);

    //GPIOPinConfigure(GPIO_PA0_U0RX);
    //GPIOPinConfigure(GPIO_PA1_U0TX);
    //GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    //GPIOPinConfigure(GPIO_PD0_M1PWM0);

    //PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    //PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, PWM_PERIOD);

    //PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 0); // start with zero speed.
    //PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
    //PWMGenEnable(PWM1_BASE, PWM_GEN_0);

    //UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    //    (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //IntPrioritySet(INT_UART0, 190);
    //IntEnable(INT_UART0);
    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    // UARTEnable(UART0_BASE);
    // IntMasterEnable();
}

int main(void) {
    // set clock to 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    
    setupPeripherals();

    if (pdTRUE != xTaskCreate(blinkRedTask, "blinkRedTask", 256, NULL, 1, NULL)) {
        while (1) ;  // Oh no!  Must not have had enough memory to create the task.
    }  
    
    vTaskStartScheduler();  // Start FreeRTOS!

    // Should never get here since the RTOS should never "exit".
    while(1) ;
    return 0;
}


// Blink red task. blink 100ms, every second
void blinkRedTask(void *pvParameters) {
    uint32_t clockFrequency = SysCtlClockGet();
    bool forward = true;

    while (1){
        if (forward) {
            //UART0Println("Forward!");
            GPIOPinWrite(GPIO_PORTF_BASE, LED1|LED2, LED1|LED2);
            forward = false;
        } else {
            //UART0Println("Not forward!");
            GPIOPinWrite(GPIO_PORTF_BASE, LED1|LED2, 0);
            forward = true;
        }
        //SysCtlDelay(clockFrequency/30); // 80Mhz. 3 ticks per delay. .1 sec = 80 000 000 / 30
        //GPIOPinWrite(GPIO_PORTF_BASE, IN1|IN2, 0);
        vTaskDelay(900); // 1ms per tick
    }

}

void vApplicationTickHook() {

}