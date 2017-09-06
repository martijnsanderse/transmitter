#include "mock_graphics.h"
#include "stdio.h"


void graphicsText(char* c, uint32_t x, uint32_t y, uint32_t foreground, uint32_t background) {
    printf("(x, y)=(%d, %d), s=%s\n", x, y, c);
}