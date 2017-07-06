#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

#define PIN_DC GPIO_PIN_1 // Also connected to red led
#define PIN_RST GPIO_PIN_2 // Also connected to blue led
#define LED_GREEN GPIO_PIN_3

void gpioInit();

void gpioResetOn();
void gpioResetOff();

void gpioDataMode();
void gpioCommandMode();


#endif //GPIO_H