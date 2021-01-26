#ifndef EVENT_SCHEDULER_H_
#define EVENT_SCHEDULER_H_

#include <stdint.h>

#define EVENT_NAME_LENGTH 10
#define EVENT_DICTIONARY_SIZE  10

typedef char event_name_t[EVENT_NAME_LENGTH];
typedef void (*event_callback_t)(void *);

typedef struct
{
    event_name_t     name;
    event_callback_t callback;
} event_pair_t;

#endif /*EVENT_SCHEDULER_H_*/
