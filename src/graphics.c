#include "graphics.h"
#include "font.h"

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8

void graphicsChar(char c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background) {
    
    // Convert the character to an index
    //c = c & 0xFF; //  0x7F;   // mask off 8th bit
    if (c < ' ') {
        c = 0;     // do not print anything under 'space'
    } else {
        c -= ' '; // subtract 32 'space' because font array starts at 'space'
    }

    const unsigned char *chr = &font[c*CHAR_WIDTH];

    // // Draw pixels
    for (uint32_t j=0; j<CHAR_WIDTH; j++) {
        for (uint32_t i=0; i<CHAR_HEIGHT; i++) {
            if (chr[j] & (1<<i)) {
                ssd1325SetPixel(x+j, y+i, foreground);
            } else {
                ssd1325SetPixel(x+j, y+i, background);
            }
        }
    }
}

void graphicsRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {

    for (uint16_t j = y; j < y+h; j++) {
        for (uint16_t i = x; i < x+w; i++) {
            
            //ssd1325Data(d);
        }
    }

}