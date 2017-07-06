/*=========================================================================
    SSD1325 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
    Select the appropriate display below to create an appropriately
    sized framebuffer, etc.
    SSD1325_128_64  128x64 pixel display
    SSD1325_128_32  128x32 pixel display
    You need to set the LCDWIDTH and LCDHEIGHT defines to an 
    appropriate size
    -----------------------------------------------------------------------*/

#include <string.h>

#include "spi.h"
#include "gpio.h"
#include "sys.h"

#define SSD1325_LCDWIDTH    128
#define SSD1325_LCDHEIGHT   64

#define SSD1325_SETCOLADDR  0x15
#define SSD1325_SETROWADDR  0x75
#define SSD1325_SETCONTRAST 0x81
#define SSD1325_SETCURRENT  0x84

#define SSD1325_SETREMAP      0xA0
#define SSD1325_SETSTARTLINE  0xA1
#define SSD1325_SETOFFSET     0xA2
#define SSD1325_NORMALDISPLAY 0xA4
#define SSD1325_DISPLAYALLON  0xA5
#define SSD1325_DISPLAYALLOFF 0xA6
#define SSD1325_INVERTDISPLAY 0xA7
#define SSD1325_SETMULTIPLEX  0xA8
#define SSD1325_MASTERCONFIG  0xAD
#define SSD1325_DISPLAYOFF    0xAE
#define SSD1325_DISPLAYON     0xAF

#define SSD1325_SETPRECHARGECOMPENABLE 0xB0
#define SSD1325_SETPHASELEN            0xB1
#define SSD1325_SETROWPERIOD           0xB2
#define SSD1325_SETCLOCK               0xB3
#define SSD1325_SETPRECHARGECOMP       0xB4
#define SSD1325_SETGRAYTABLE           0xB8
#define SSD1325_SETPRECHARGEVOLTAGE    0xBC
#define SSD1325_SETVCOMLEVEL           0xBE
#define SSD1325_SETVSL                 0xBF

#define SSD1325_GFXACCEL 0x23
#define SSD1325_DRAWRECT 0x24
#define SSD1325_COPY     0x25

void ssd1325Reset(void);
void ssd1325Command(uint8_t c);
void ssd1325Data(uint8_t c);
void ssd1325Init(void);
void ssd1325Display(void);
void ssd1325SetPixel(uint32_t x, uint32_t y, uint32_t value);
void ssd1325ClearBuffer(void);

