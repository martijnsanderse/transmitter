#ifndef MOCK_SSD1325_H
#define MOCK_SSD1325_H

#include <stdint.h>


//uint32_t receivedPixelValues[8][5] = {0};

uint32_t getReceivedValue(uint32_t x, uint32_t y);

void ssd1325SetPixel(uint32_t x, uint32_t y, uint32_t value);
void ssd1325Display(void);
void ssd1325ClearBuffer(void);


#endif // MOCK_SSD1325_H