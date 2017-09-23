#include "mock_queue.h"
#include "stdio.h"


enum UIEvent* events;
uint32_t numberOfEvents = 0;
uint32_t currentEvent = 0;

void setEvents(uint32_t newNumberOfEvents, enum UIEvent* newEvents) {
    events = newEvents;
    numberOfEvents = newNumberOfEvents;
}

long xQueueGenericReceive( void * xQueue, void * pvBuffer, uint32_t xTicksToWait, const long xJustPeek ) {
    printf("queueReceive called\n");
    printf("returning event index: %d, value: %d", currentEvent, events[currentEvent]);
    if (currentEvent < numberOfEvents) {
        memcpy( ( void * ) pvBuffer, ( void * ) &events[currentEvent], sizeof(enum UIEvent) );
        printf("sizeof: %d\n", sizeof(enum UIEvent));
        currentEvent++;
    } else {
        enum UIEvent final = EXIT;
        memcpy( ( void * ) pvBuffer, ( void * ) &final, sizeof(enum UIEvent) );
    }

}