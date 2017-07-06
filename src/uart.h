#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"


void uartInit(void);
void uartPrintln(const char *buf);

#endif //UART_H