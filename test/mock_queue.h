#ifndef MOCK_QUEUE_H
#define MOCK_QUEUE_H

#include "stdint.h"
#include "stdbool.h"
#include "event.h"

// This mock allows to fill up a queue beforehand with an array of events
// Every time xQueueReceive is called, the next event is returned.
//
// When xQueueReceive is called and there are no more events, then
// .... what happens?

//typedef uint32_t BaseType_t ;
//typedef uint32_t QueueHandle_t;
//typedef uint32_t TickType_t;
//typedef uint32_t pdFALSE ;


void setEvents(uint32_t numberOfEvents, enum UIEvent* events);

long xQueueGenericReceive( void * xQueue, void * pvBuffer, uint32_t xTicksToWait, const long xJustPeek );

#define xQueueReceive( xQueue, pvBuffer, xTicksToWait ) xQueueGenericReceive( ( xQueue ), ( pvBuffer ), ( xTicksToWait ), pdFALSE )



#endif //MOCK_QUEUE_H