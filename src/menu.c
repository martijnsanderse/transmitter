#include "menu.h"
#include "graphics.h"
#include "ssd1325.h"
#include "gpio.h" // for UIEvent
#include "uart.h" // for debugs


void display_menu(struct state* state) {
    uartPrintln("enter display_menu");
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

// state function for displaying menu
// and waiting for input, and determine what to do next.
void displaying_menu(struct state * state) { 
    uartPrintln("enter displaying_menu");
    // display menu first
    display_menu(state);

    state->next = 0;
    
    // then wait for input, and determine what to do next.
    if (rxQueue != 0) {
        enum UIEvent event = UP;
        xQueueReceive(rxQueue, &event, portMAX_DELAY);
        switch(event) {
            case UP:
                uartPrintln("Received up");
                // update state
                if (state->current_node->prev)
                    state->current_node = state->current_node->prev;
                // prepare for the next state transition
                state->next = state->current_node->on_click_state;
                break;
            case DOWN:
                uartPrintln("Received down");
                // update state
                if (state->current_node->next)
                    state->current_node = state->current_node->next;
                // prepare for the next state transition
                state->next = state->current_node->on_click_state;
                break;
            case BACK:
                uartPrintln("Received back");
                // update state
                if (state->current_node->parent)
                    state->current_node = state->current_node->parent;
                break;
            case SELECT:
                uartPrintln("Received select");
                if (state->current_node->child)
                    state->current_node = state->current_node->child;
                break;
            default:
                // prepare for the next state transition
                state->next = 0;
                break;
        }
    }
}

void menuInitNode(struct node* s, char* n, struct node* pr, struct node* ne, struct node* pa, struct node* ch) {
    s->name = n;
    s->prev = pr;
    s->next = ne;
    s->parent = pa;
    s->child = ch;
    s->on_click_state = displaying_menu;
}

void menuStartLoop(struct node* rootNode)
{    
    
    struct state state = { displaying_menu, rootNode };
    while(state.next) state.next(&state);

}
