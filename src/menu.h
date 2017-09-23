#ifndef MENU_H
#define MENU_H

#include "FreeRTOS.h"
#include "queue.h"

typedef void state_fn(struct state *);

struct state
{
    state_fn * next;
    struct node* current_node; // current menu item
};

struct node {
    char *name;
    
    struct node* prev;   // link to previous node on current level of hierarchy
    struct node* next;   // link to next node on current level of hierarchy
    struct node* parent; // link to first item one level up
    struct node* child;  // link to first item one level down

    state_fn * on_click_state;
};

void display_home_screen(struct state* state);
void display_menu(struct state* state);

void displaying_home_screen(struct state * state);
void displaying_menu(struct state * state);

void menuInitNode(struct node* s, char* n, struct node* pr, struct node* ne, struct node* pa, struct node* ch, state_fn* next_state_funtion);
void menuStartLoop(struct node* rootNode, QueueHandle_t queue);



#endif // MENU_H