#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#include "ssd1325.h"


void graphicsRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void graphicsChar(char c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background);

#endif // GRAPHICS_H