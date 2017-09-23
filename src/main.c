#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
//#include "semphr.h"
#include "portmacro.h"

#include "ssd1325.h"
#include "event.h"
#include "uart.h"
#include "graphics.h"
#include "menu.h"

QueueHandle_t rxQueue;

// task prototypes
void showMenuTask(void *);  // prototype so we can include it in main while the code is underneath

int main(void) {
    // set clock to 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    ssd1325Init();
    ssd1325Display();

    uartInit();
    uartPrintln("Start");


    rxQueue = xQueueCreate(10, sizeof(enum UIEvent));
    if (rxQueue == NULL) {
        uartPrintln("no Queue\r\n");
    } else {
        uartPrintln("Queue OK.");
    }
    
    if (pdTRUE != xTaskCreate(showMenuTask, "showMenuTask", 256, NULL, 1, NULL)) {
        while (1) ;  // Oh no!  Must not have had enough memory to create the task.
    }  
    
    vTaskStartScheduler();  // Start FreeRTOS!

    // Should never get here since the RTOS should never "exit".
    while(1);
    return 0;
}


// Blink red task. blink 100ms, every second
void showMenuTask(void *pvParameters) {
    
    uartPrintln("Start task.");
    gpioLedGreen(true);
    vTaskDelay(100);
    gpioLedGreen(false);
    vTaskDelay(100);

    while (1) {

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

        menuInitNode(&menu1   , "select model"   , 0        , &menu2   , &home  , &menu1_1 , displaying_menu);
        menuInitNode(&menu2   , "add model"   , &menu1   , &menu3   , &home  , &menu2_1 , displaying_menu);
        menuInitNode(&menu3   , "edit model"   , &menu2   , 0        , &home  , &menu3_1 , displaying_menu);

        menuInitNode(&menu1_1 , "menu 1.1" , 0        , &menu1_2 , &menu1 , 0        , displaying_menu);
        menuInitNode(&menu1_2 , "menu 1.2" , &menu1_1 , 0        , &menu1 , 0        , displaying_menu);

        menuInitNode(&menu2_1 , "menu 2.1" , 0        , &menu2_2 , &menu2 , 0        , displaying_menu);
        menuInitNode(&menu2_2 , "menu 2.2" , &menu2_1 , &menu2_3 , &menu2 , 0        , displaying_menu);
        menuInitNode(&menu2_3 , "menu 2.3" , &menu2_2 , 0        , &menu2 , 0        , displaying_menu);

        menuInitNode(&menu3_1 , "edit name" , 0        , &menu3_2 , &menu3 , 0        , displaying_menu);
        menuInitNode(&menu3_2 , "configure channels" , &menu3_1 , &menu3_3 , &menu3 , 0        , displaying_menu);
        menuInitNode(&menu3_3 , "delete" , &menu3_2 , 0 , &menu3 , 0        , displaying_menu);

        menuStartLoop(&home, rxQueue);
        uartPrintln("exited menu loop");

        vTaskDelay(1000);        
    }

}

void vApplicationTickHook() {

}