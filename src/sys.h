#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"

void sysDelay(uint32_t milliseconds);
void sysSetClock(void);

#endif //SYS_H