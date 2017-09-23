#include "mock_ssd1325.h"
#include <stdio.h>

uint32_t receivedPixelValues[64][128] = {0};


uint32_t getReceivedValue(uint32_t x, uint32_t y) {
    return receivedPixelValues[y][x];
}

void ssd1325SetPixel(uint32_t x, uint32_t y, uint32_t value) {
    // store all values triplets at their x,y positions
    receivedPixelValues[y][x] = value;
    //printf("ssd1325SetPixel %d, %d, %d\n", x, y, value);
}

void ssd1325Display(void) {

}

void ssd1325ClearBuffer(void) {
    
}