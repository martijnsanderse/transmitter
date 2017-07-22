#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "queue.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#define PIN_DC GPIO_PIN_1
#define PIN_RST GPIO_PIN_2

#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

QueueHandle_t rxQueue;

void gpioInit();

void gpioResetOn();
void gpioResetOff();

void gpioDataMode();
void gpioCommandMode();

void gpioLedRed(bool high);
void gpioLedBlue(bool high);
void gpioLedGreen(bool high);


#endif //GPIO_H