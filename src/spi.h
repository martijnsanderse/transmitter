#ifndef SPI_H
#define SPI_H

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

void spiInit(void);
void spiWrite(uint8_t byte);

#endif //SPI_H