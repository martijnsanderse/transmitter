#include "unity.h"
#include "menu.h"
#include "mock_graphics.h"
#include "mock_queue.h"
#include "event.h"

// test cases
void test_menu(void)
{
    // declare empty nodes
    // declare empty nodes
    struct node home;

    struct node menu1;
    struct node menu2;
    struct node menu3;

    struct node menu1_1;
    struct node menu1_2;

    struct node menu2_1;
    struct node menu2_2;
    struct node menu2_3;

    struct node menu3_1;
    struct node menu3_2;
    struct node menu3_3;
    struct node menu3_4;

    // initialize all nodes. This step defines the menu structure.
    // init(struct_to_init_ptr, name, previous, next, parent, child, next_state_function)
    menuInitNode(&home    , "home"     , 0        , 0        , 0      , &menu1   , displaying_home_screen);

    menuInitNode(&menu1   , "menu 1"   , 0        , &menu2   , &home  , &menu1_1 , displaying_menu);
    menuInitNode(&menu2   , "menu 2"   , &menu1   , &menu3   , &home  , &menu2_1 , displaying_menu);
    menuInitNode(&menu3   , "menu 3"   , &menu2   , 0        , &home  , &menu3_1 , displaying_menu);

    menuInitNode(&menu1_1 , "menu 1.1" , 0        , &menu1_2 , &menu1 , 0        , displaying_menu);
    menuInitNode(&menu1_2 , "menu 1.2" , &menu1_1 , 0        , &menu1 , 0        , displaying_menu);

    menuInitNode(&menu2_1 , "menu 2.1" , 0        , &menu2_2 , &menu2 , 0        , displaying_menu);
    menuInitNode(&menu2_2 , "menu 2.2" , &menu2_1 , &menu2_3 , &menu2 , 0        , displaying_menu);
    menuInitNode(&menu2_3 , "menu 2.3" , &menu2_2 , 0        , &menu2 , 0        , displaying_menu);

    menuInitNode(&menu3_1 , "menu 3.1" , 0        , &menu3_2 , &menu3 , 0        , displaying_menu);
    menuInitNode(&menu3_2 , "menu 3.2" , &menu3_1 , &menu3_3 , &menu3 , 0        , displaying_menu);
    menuInitNode(&menu3_3 , "menu 3.3" , &menu3_2 , &menu3_4 , &menu3 , 0        , displaying_menu);
    menuInitNode(&menu3_4 , "menu 3.4" , &menu3_3 , 0        , &menu3 , 0        , displaying_menu);
    // before starting the menu, fill up the queue with some events
    enum UIEvent events[] = {SELECT, BACK, UP, DOWN, EXIT};
    setEvents(5, events);

    long fakeQueueHandle = 33;

    menuStartLoop(&menu1, fakeQueueHandle);

    TEST_ASSERT_EQUAL(3,3);
}


// start runner
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_menu);
    return UNITY_END();
}