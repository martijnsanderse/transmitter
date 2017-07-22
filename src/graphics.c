#include "graphics.h"
#include "font.h"

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 8



void graphicsChar(char c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background) {
    
        // Convert the character to an index
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }

    uint8_t *chr = font+(c*CHAR_WIDTH); //&font[c*CHAR_WIDTH];

    // Draw pixels
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