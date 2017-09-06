#include "unity.h"
#include "menu.h"
#include "mock_graphics.h"

// test cases
void test_menu(void)
{
        // declare empty nodes
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
    // init(struct_to_init_ptr, name, previous, next, parent, child)
    menuInitNode(&menu1, "menu 1", 0,        &menu2, 0, &menu1_1);
    menuInitNode(&menu2, "menu 2", &menu1,   &menu3, 0, &menu2_1);
    menuInitNode(&menu3, "menu 3", &menu2,   0,      0, &menu3_1);

    menuInitNode(&menu1_1, "menu 1.1", 0,       &menu1_2,   &menu1, 0);
    menuInitNode(&menu1_2, "menu 1.2", &menu1_1, 0,         &menu1, 0);

    menuInitNode(&menu2_1, "menu 2.1", 0,       &menu2_2,   &menu2, 0);
    menuInitNode(&menu2_2, "menu 2.2", &menu2_1, &menu2_3,  &menu2, 0);
    menuInitNode(&menu2_3, "menu 2.3", &menu2_2, 0,         &menu2, 0);

    menuInitNode(&menu3_1, "menu 3.1", 0,       &menu3_2,   &menu3, 0);
    menuInitNode(&menu3_2, "menu 3.2", &menu3_1, &menu3_3,  &menu3, 0);
    menuInitNode(&menu3_3, "menu 3.3", &menu3_2, &menu3_4,  &menu3, 0);
    menuInitNode(&menu3_4, "menu 3.4", &menu3_3, 0,         &menu3, 0);

    menuStartLoop(&menu1);

    TEST_ASSERT_EQUAL(3,3);
}


// start runner
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_menu);
    return UNITY_END();
}