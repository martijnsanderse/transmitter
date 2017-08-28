#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "ssd1325.h" 


void graphicsChar(char c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background);
void graphicsText(char* c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background);

#endif // GRAPHICS_H