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
#include "inc/hw_types.h" // for HWREG
#include "inc/hw_gpio.h"

#define PIN_DC GPIO_PIN_1
#define PIN_RST GPIO_PIN_2

#define SW_SELECT GPIO_PIN_1
#define SW_BACK GPIO_PIN_4
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

enum UIEvent {
    UP,
    DOWN,
    SELECT,
    BACK
};

QueueHandle_t rxQueue;

void gpioInit();

void gpioResetOn();
void gpioResetOff();

void gpioDataMode();
void gpioCommandMode();

void gpioLedBlue(bool high);
void gpioLedGreen(bool high);


#endif //GPIO_H