#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

//#ifdef TEST
//#include "../test/mock_ssd1325.h"
//#else
#include "ssd1325.h" // include normal forward declarations
//#endif

void graphicsRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void graphicsChar(char c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background);

#endif // GRAPHICS_H