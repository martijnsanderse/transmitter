#include "gpio.h"


void gpioInit(void) {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    // configure pins 1,2 and 3 for output 
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, PIN_DC|PIN_RST);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);
    // Set all outputs to zero
    GPIOPinWrite(GPIO_PORTE_BASE, PIN_DC|PIN_RST, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN, 0);
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

void gpioLedRed(bool high) {
    if (high) {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, LED_RED);
    } else {
        GPIOPinWrite(GPIO_PORTF_BASE, LED_RED, 0);
    }
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





