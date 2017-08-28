#include <string.h>

#include "spi.h"
#include "gpio.h"
#include "sys.h"

#include "ssd1325.h"



// the memory buffer for the LCD
static uint8_t buffer[SSD1325_LCDHEIGHT * SSD1325_LCDWIDTH / 2] = {0};


void ssd1325Reset(void) {
    // delay a ms
    sysDelay(1);
    // perform reset
    gpioResetOn();
    sysDelay(10);
    // back to normal
    gpioResetOff();
    sysDelay(500);
}

void ssd1325Command(uint8_t c) {
    gpioCommandMode();  
    sysDelay(1);
    // send using blocking function.
    // when function returns, data is in send fifo.
    spiWrite(c);
    sysDelay(1); // not sure when data is actually send.s
    // back to default
    gpioDataMode();
}

void ssd1325Data(uint8_t c) {
    // data mode is supposed to be on always.
    spiWrite(c);
}

void ssd1325Init(void) {
    // For sending pixel data and commands to an SSD1325 we need:
    //   - data/command IO pin
    //   - SPI
    
    gpioInit();
    spiInit();

    // set IO pins to default level
    // reset pin is normally high
    // dc pin in normally high --> we expect to write data more often than commands.
    gpioResetOff();
    gpioDataMode();
    
    // reset display
    ssd1325Reset();

    ssd1325Command(SSD1325_DISPLAYOFF); /* display off */
    ssd1325Command(SSD1325_SETCLOCK); /* set osc division */
    ssd1325Command(0xF1); /* 145 */
    ssd1325Command(SSD1325_SETMULTIPLEX ); /* multiplex ratio */
    ssd1325Command(0x3f); /* duty = 1/64 */
    ssd1325Command(SSD1325_SETOFFSET); /* set display offset --- */
    ssd1325Command(0x4C); /* 76 */
    ssd1325Command(SSD1325_SETSTARTLINE); /*set start line */
    ssd1325Command(0x00); /* ------ */
    ssd1325Command(SSD1325_MASTERCONFIG); /*Set Master Config DC/DC Converter*/
    ssd1325Command(0x02);
    ssd1325Command(SSD1325_SETREMAP); /* set segment remap------ */
    //command(0x56); // pixels go top-down, then left-right
    ssd1325Command(0x52);   // pixels go left-right, then top-down
    ssd1325Command(SSD1325_SETCURRENT + 0x2); /* Set Full Current Range */
    //command(SSD1325_SETCURRENT + 0x0); /* Set Quarter Current Range */
    ssd1325Command(SSD1325_SETGRAYTABLE);
    ssd1325Command(0x01);
    ssd1325Command(0x11);
    ssd1325Command(0x22);
    ssd1325Command(0x32);
    ssd1325Command(0x43);
    ssd1325Command(0x54);
    ssd1325Command(0x65);
    ssd1325Command(0x76);

    ssd1325Command(SSD1325_SETCONTRAST); /* set contrast current */
    ssd1325Command(0x7F);  // max!
  
    ssd1325Command(SSD1325_SETROWPERIOD);
    ssd1325Command(0x51);
    ssd1325Command(SSD1325_SETPHASELEN);
    ssd1325Command(0x55);
    ssd1325Command(SSD1325_SETPRECHARGECOMP);
    ssd1325Command(0x02);
    ssd1325Command(SSD1325_SETPRECHARGECOMPENABLE);
    ssd1325Command(0x28);
    ssd1325Command(SSD1325_SETVCOMLEVEL); // Set High Voltage Level of COM Pin
    ssd1325Command(0x1C); //?
    ssd1325Command(SSD1325_SETVSL); // set Low Voltage Level of SEG Pin 
    ssd1325Command(0x0D|0x02);
  
    ssd1325Command(SSD1325_NORMALDISPLAY); /* set display mode */

  /* Clear Screen */  
 // command(0x23); /*set graphic acceleration commmand */
 // command(SSD1325_GFXACCEL);
 // command(SSD1325_DRAWRECT); /* draw rectangle */
 // command(0x00); /* Gray Scale Level 1 */
 // command(0x00); /* Gray Scale Level 3 & 2 */
 // command(0x3f); /* Gray Scale Level 3 & 2 */
 // command(0x3f); /* Gray Scale Level 3 & 2 */
 // command(0x00); /* Gray Scale Level 3 & 2 */

    ssd1325Command(SSD1325_DISPLAYON); /* display ON */
}

void ssd1325Display(void) {
    // write buffer to display

    ssd1325Command(SSD1325_SETCOLADDR); /* set column address */
    ssd1325Command(0x00); /* set column start address */
    ssd1325Command(0x3f);  /* set column end address */
    ssd1325Command(SSD1325_SETROWADDR); /* set row address */
    ssd1325Command(0x00); /* set row start address */
    ssd1325Command(0x3f); /* set row end address */

    uint32_t numberOfPixels = SSD1325_LCDHEIGHT * SSD1325_LCDWIDTH / 2; 
    for (uint32_t i=0; i<numberOfPixels; i++) {
        ssd1325Data(buffer[i]);
    }
}

void ssd1325ClearBuffer(void) {
    // clear buffer;
    memset(buffer, 0, SSD1325_LCDHEIGHT * SSD1325_LCDWIDTH / 2);
}

void ssd1325SetPixel(uint32_t x, uint32_t y, uint32_t value) {
    // two pixels are stored in one byte.
    // higher nibble contains a value for pixel at (0,0), 
    // lower nibble contains a value for the next pixel at (1,0).

    //s

    // is x even? 
    if ((x%2) == 0) {
        uint8_t currentLowerNibble = buffer[x/2 + y*(SSD1325_LCDWIDTH / 2)] & 0x0F;
        uint8_t newUpperNibble = value<<4;
        buffer[x/2 + y*(SSD1325_LCDWIDTH / 2)] = newUpperNibble + currentLowerNibble;
    } else {
        uint8_t newLowerNibble = value;
        uint8_t currentUpperNibble = buffer[x/2 + y*(SSD1325_LCDWIDTH / 2)] & 0xF0;
        buffer[x/2 + y*(SSD1325_LCDWIDTH / 2)] = currentUpperNibble | newLowerNibble;
    }
}