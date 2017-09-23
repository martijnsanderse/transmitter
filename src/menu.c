#include "menu.h"
#include "graphics.h"
#include "ssd1325.h"
//#include "gpio.h"
#include "event.h"

QueueHandle_t rxQueue;

void display_menu(struct state* state) {
    // print colors
    uint32_t default_fg = 10;
    uint32_t default_bg = 0;
    uint32_t active_fg = 15;
    uint32_t active_bg = 1;

    ssd1325ClearBuffer();
    // if available, print previous item
    if (state->current_node->prev)
        graphicsText(state->current_node->prev->name, 0, 0, default_fg, default_bg);
    // diplay current menu item
    graphicsText(state->current_node->name, 0, 10, active_fg, active_bg);
    // if available, print next item
    if (state->current_node->next)
        graphicsText(state->current_node->next->name, 0, 20, default_fg, default_bg);
    ssd1325Display();
}

void display_home_screen(struct state* state) {
    // print colors
    uint32_t default_fg = 10;
    uint32_t default_bg = 0;
    uint32_t active_fg = 15;
    uint32_t active_bg = 1;
    ssd1325ClearBuffer();
    graphicsText("home screen", 35, 25, default_fg, default_bg);
    graphicsText("placeholder", 35, 35, default_fg, default_bg);
    ssd1325Display();
}

// state function for showing main screen
void displaying_home_screen(struct state * state) {
    // display menu first
    display_home_screen(state);
    
    // then wait for input, and determine what to do next.
    if (rxQueue != 0) {
        enum UIEvent event = UP;
        xQueueReceive(rxQueue, &event, portMAX_DELAY);
        switch(event) {
            case SELECT:
                // update position in the tree
                if (state->current_node->child)
                    state->current_node = state->current_node->child;
                // set next state function
                state->next = state->current_node->on_click_state;
                break;
            case BACK:
            case DOWN:
            case UP:
                // do nothing
                break;
            case EXIT:
            default:
                // prepare for the exit the menu loop in the next round.
                state->next = 0;
                break;
        }
    }
}


// state function for displaying menu
// and waiting for input, and determine what to do next.
void displaying_menu(struct state * state) { 
    // display menu first
    display_menu(state);
    
    // then wait for input, and determine what to do next.
    if (rxQueue != 0) {
        enum UIEvent event = UP;
        xQueueReceive(rxQueue, &event, portMAX_DELAY);
        switch(event) {
            case UP:
                // update position in the tree
                if (state->current_node->prev)
                    state->current_node = state->current_node->prev;
                // set next state function
                state->next = state->current_node->on_click_state;
                break;
            case DOWN:
                // update position in the tree
                if (state->current_node->next)
                    state->current_node = state->current_node->next;
                // set next state function
                state->next = state->current_node->on_click_state;
                break;
            case BACK:
                // update position in the tree
                if (state->current_node->parent)
                    state->current_node = state->current_node->parent;
                // set next state function
                state->next = state->current_node->on_click_state;
                break;
            case SELECT:
                // update position in the tree
                if (state->current_node->child)
                    state->current_node = state->current_node->child;
                // set next state function
                state->next = state->current_node->on_click_state;
                break;
            case EXIT:
            default:
                // prepare for the exit the menu loop in the next round.
                state->next = 0;
                break;
        }
    }
}

void menuInitNode(struct node* s, char* n, struct node* pr, struct node* ne, struct node* pa, struct node* ch, state_fn* next_state_funtion) {
    s->name = n;
    s->prev = pr;
    s->next = ne;
    s->parent = pa;
    s->child = ch;
    s->on_click_state = next_state_funtion;
}

void menuStartLoop(struct node* rootNode, QueueHandle_t queue)
{    
    rxQueue = queue;
    struct state state = { rootNode->on_click_state, rootNode };
    while(state.next) state.next(&state);

}
