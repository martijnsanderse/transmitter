#include "gpio.h"


void gpioInit(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // configure pins 1,2 and 3 for output 
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, PIN_DC|PIN_RST|LED_GREEN);
    // Set all outputs to zero
    GPIOPinWrite(GPIO_PORTF_BASE, PIN_DC|PIN_RST|LED_GREEN, 0);
}

void gpioResetOn(void){
	// Reset is active when low
	GPIOPinWrite(GPIO_PORTF_BASE, PIN_RST, 0);
}

void gpioResetOff(void){
	// reset is not active when high
	GPIOPinWrite(GPIO_PORTF_BASE, PIN_RST, PIN_RST);
}

void gpioCommandMode(void){
	// command mode is active when low
	GPIOPinWrite(GPIO_PORTF_BASE, PIN_DC, 0);	
}

void gpioDataMode(void){
	// data mode is active when high
	GPIOPinWrite(GPIO_PORTF_BASE, PIN_DC, PIN_DC);
}




