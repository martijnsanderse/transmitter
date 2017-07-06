#include "sys.h"


void sysDelay(uint32_t milliseconds) {
    // Not an accurate delay, do not use for timing.
    // A delay instructions is about 3 cycles.
    SysCtlDelay((SysCtlClockGet()/3/1000) * milliseconds);
}

void sysSetClock(void) {
	// set clock frequency at 40 MHz
   SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
} 
    