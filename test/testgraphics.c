#include "unity.h"
#include "graphics.h"
#include "mock_ssd1325.h"
#include <stdio.h>

// test inputs
char test_char = 'a';
uint32_t test_x = 0;
uint32_t test_y = 0;
uint32_t test_fg = 15;
uint32_t test_bg = 1;

// expected outputs
uint32_t expectedPixelValues[8][5] =  {
    {  1,  1,  1,  1,  1 },
    {  1,  1,  1,  1,  1 },
    {  1,  1,  1,  1,  1 },
    {  1, 15, 15, 15,  1 },
    {  1,  1,  1,  1, 15 },
    {  1, 15, 15, 15, 15 },
    { 15,  1,  1,  1, 15 },
    {  1, 15, 15, 15, 15 }
};

// test cases
void test_graphicsChar(void)
{
    // arrange

    // act 
    graphicsChar(test_char, test_x, test_y, test_fg, test_bg);
    
    // assert
    for (uint32_t y = 0; y < 8; y++) {
        for (uint32_t x = 0; x < 5; x++) {
            printf("testing value for x,y = %d, %d", x, test_y);
            TEST_ASSERT_EQUAL(expectedPixelValues[y][x], getReceivedValue(x, y));
        }
    }
}

// start runner
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_graphicsChar);
    return UNITY_END();
}