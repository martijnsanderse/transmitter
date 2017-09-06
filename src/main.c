/*
 * main.c
 */

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

// #include "inc/hw_types.h"
// #include "inc/hw_gpio.h"
// #include "inc/hw_memmap.h"
// #include "inc/hw_sysctl.h"
// #include "inc/hw_ints.h"
// #include "driverlib/gpio.h"
// #include "driverlib/sysctl.h"
// #include "driverlib/pin_map.h"
// #include "driverlib/interrupt.h"
// #include "driverlib/uart.h"
// #include "driverlib/adc.h"
// #include "driverlib/pwm.h"
// #include "driverlib/qei.h"

// #define LED1 GPIO_PIN_1
// #define LED2 GPIO_PIN_2
//#define PWM_PERIOD 8000 // so pwm at 10kHz if 80Mhz clock.

#include "ssd1325.h"
#include "gpio.h" // for rxQueue and UIEvent
#include "uart.h"
#include "graphics.h"
#include "menu.h"

// task prototypes
    
void blinkRedTask(void *);  // prototype so we can include it in main while the code is underneath

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
    
    if (pdTRUE != xTaskCreate(blinkRedTask, "blinkRedTask", 256, NULL, 1, NULL)) {
        while (1) ;  // Oh no!  Must not have had enough memory to create the task.
    }  
    
    vTaskStartScheduler();  // Start FreeRTOS!

    // Should never get here since the RTOS should never "exit".
    while(1);
    return 0;
}


// Blink red task. blink 100ms, every second
void blinkRedTask(void *pvParameters) {
    
    uartPrintln("Start task.");
    gpioLedGreen(true);
    vTaskDelay(100);
    gpioLedGreen(false);
    vTaskDelay(100);

    // gpioLedBlue(true);
    // vTaskDelay(100);
    // gpioLedBlue(false);
    // vTaskDelay(100);

    // gpioLedGreen(true);
    // vTaskDelay(100);
    // gpioLedGreen(false);
    // vTaskDelay(100);



    while (1){
        //uartPrintln("Task loop.");
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        //vTaskDelay(10);
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

        // if (rxQueue != 0) {
        //     while (uxQueueMessagesWaiting(rxQueue) > 0) {

        //         enum UIEvent event = UP;
        //         xQueueReceive(rxQueue, &event, (TickType_t)10);

        //         switch (event) {
        //             case UP:
        //                 uartPrintln("up");
        //                 break;
        //             case DOWN:
        //                 uartPrintln("down");
        //                 break;
        //             case SELECT:
        //                 uartPrintln("select");
        //                 break;
        //             case BACK:
        //                 uartPrintln("back");
        //                 break;
        //             default:
        //                 uartPrintln("no!");
        //                 break;

        //         } 
        //     }
        // }

        // //char* text = "Hello.";
        // ssd1325ClearBuffer();
        // //ssd1325SetPixel(64, 32, 10);
        // // graphicsText(text,10,20,15,1);
        // // ssd1325Display();
        
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
        uartPrintln("exited menu loop");

        vTaskDelay(1000);

        //SysCtlDelay(clockFrequency/30); // 80Mhz. 3 ticks per delay. .1 sec = 80 000 000 / 30
        //GPIOPinWrite(GPIO_PORTF_BASE, IN1|IN2, 0);
        
    }

}

void vApplicationTickHook() {

}