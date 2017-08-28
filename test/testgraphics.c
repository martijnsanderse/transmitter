#include "unity.h"
#include "graphics.h"
#include "mock_ssd1325.h"
#include <stdio.h>



// expected outputs
uint32_t expectedPixelValuesChar_a[8][5] =  {
    {  1,  1,  1,  1,  1 },
    {  1,  1,  1,  1,  1 },
    {  1,  1,  1,  1,  1 },
    {  1, 15, 15, 15,  1 },
    {  1,  1,  1,  1, 15 },
    {  1, 15, 15, 15, 15 },
    { 15,  1,  1,  1, 15 },
    {  1, 15, 15, 15, 15 }
};

uint32_t expectedPixelValuesChar_b[8][5] =  {
    {  15,  1,  1,  1,  1 },
    {  15,  1,  1,  1,  1 },
    {  15,  1,  1,  1,  1 },
    {  15, 15, 15, 15,  1 },
    {  15,  1,  1,  1, 15 },
    {  15,  1,  1,  1, 15 },
    {  15,  1,  1,  1, 15 },
    {  15,  15, 15, 15, 1 }
};

uint32_t expectedPixelValuesChar_c[8][5] =  {
    {   1,  1,  1,  1,  1 },
    {   1,  1,  1,  1,  1 },
    {   1,  1,  1,  1,  1 },
    {   1, 15, 15, 15, 15 },
    {  15,  1,  1,  1,  1 },
    {  15,  1,  1,  1,  1 },
    {  15,  1,  1,  1,  1 },
    {   1, 15, 15, 15, 15 }
};

// test cases
void test_graphicsChar(void)
{
    // arrange
    // test inputs
    char test_char = 'a';
    uint32_t test_x = 3;
    uint32_t test_y = 2;
    uint32_t test_fg = 15;
    uint32_t test_bg = 1;

    const uint32_t disp_w = 128;
    const uint32_t disp_h = 64;
    uint32_t char_w = 5;
    uint32_t char_h = 8;

    uint32_t expectedPixelValues[disp_h][disp_w] = {0}; // entire display
    for (uint32_t y = 0; y < char_h; y++) {
        for (uint32_t x = 0; x < char_w; x++) {
            expectedPixelValues[y+test_y][x+test_x] = expectedPixelValuesChar_a[y][x];
        }
    }

    // act 
    graphicsChar(test_char, test_x, test_y, test_fg, test_bg);
    
    // assert
    for (uint32_t y = 0; y < disp_h; y++) {
        for (uint32_t x = 0; x < disp_w; x++) {
            TEST_ASSERT_EQUAL(expectedPixelValues[y][x], getReceivedValue(x, y));
        }
    }
}

void test_graphicsText(void)
{
    // arrange
    // test inputs
    char test_char = 'a';
    uint32_t test_x = 3;
    uint32_t test_y = 2;
    uint32_t test_fg = 15;
    uint32_t test_bg = 1;

    const uint32_t disp_w = 128;
    const uint32_t disp_h = 64;
    uint32_t char_w = 5;
    uint32_t char_h = 8;

    // blank pixel array
    uint32_t expectedPixelValues[disp_h][disp_w] = {0}; // entire display
    // write "a"
    for (uint32_t y = 0; y < char_h; y++) {
        for (uint32_t x = 0; x < char_w; x++) {
            expectedPixelValues[y+test_y][x+test_x] = expectedPixelValuesChar_a[y][x];
        }
    }
    // write "b"
    for (uint32_t y = 0; y < char_h; y++) {
        for (uint32_t x = 0; x < char_w; x++) {
            expectedPixelValues[y+test_y][x+test_x+char_w+1] = expectedPixelValuesChar_b[y][x];
        }
    }
    // write "c"
    for (uint32_t y = 0; y < char_h; y++) {
        for (uint32_t x = 0; x < char_w; x++) {
            expectedPixelValues[y+test_y][x+test_x+(char_w+1)*2] = expectedPixelValuesChar_c[y][x];
        }
    }


    // act 
    char* text = "abc";
    graphicsText(text, test_x, test_y, test_fg, test_bg);
    
    // assert
    for (uint32_t y = 0; y < disp_h; y++) {
        for (uint32_t x = 0; x < disp_w; x++) {
            TEST_ASSERT_EQUAL(expectedPixelValues[y][x], getReceivedValue(x, y));
        }
    }
}

// start runner
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_graphicsChar);
    RUN_TEST(test_graphicsText);
    return UNITY_END();
}