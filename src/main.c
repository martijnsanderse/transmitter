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
#include "gpio.h" // for rxQueue
#include "uart.h"
#include "graphics.h"

// task prototypes
    
void blinkRedTask(void *);  // prototype so we can include it in main while the code is underneath

int main(void) {
    // set clock to 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    ssd1325Init();
    ssd1325Display();

    uartInit();
    uartPrintln("Start");

    // rxQueue = xQueueCreate(10, sizeof(uint32_t));
    // if (rxQueue == NULL) {
    //     uartPrintln("no Queue\r\n");
    // } else {
    //     uartPrintln("Queue OK.");
    // }
    
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
    gpioLedRed(true);
    vTaskDelay(100);
    gpioLedRed(false);
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
        uartPrintln("Task loop.");
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        //vTaskDelay(10);
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

        // if (rxQueue != 0) {
        //     while (uxQueueMessagesWaiting(rxQueue) > 0) {

        //         int32_t direction = 0;
        //         xQueueReceive(rxQueue, &direction, (TickType_t)10);

        //         if (direction) {
        //             uartPrintln("up");
        //         } else {
        //             uartPrintln("down");
        //         }
        //     }
        // }

        ssd1325ClearBuffer();
        ssd1325SetPixel(64, 32, 10);
        graphicsChar('a',100,20,15,1);
        ssd1325Display();
        vTaskDelay(1000);

        //SysCtlDelay(clockFrequency/30); // 80Mhz. 3 ticks per delay. .1 sec = 80 000 000 / 30
        //GPIOPinWrite(GPIO_PORTF_BASE, IN1|IN2, 0);
        
    }

}

void vApplicationTickHook() {

}