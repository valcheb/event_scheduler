#include "event_scheduler.h"
#include "event_order_ring.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//TODO pass param to callback

static event_pair_t event_dictionary[EVENT_DICTIONARY_SIZE];
static event_order_ring_t event_order_ring;
static event_name_t event_names[EVENT_DICTIONARY_SIZE];

void event_subscribe(const char *name, event_callback_t callback)
{
    static uint16_t idx = 0;

    if (event_order_ring.size == 0)
    {
        eor_init(&event_order_ring, event_names, EVENT_DICTIONARY_SIZE);
    }

    if (idx >= EVENT_DICTIONARY_SIZE)
    {
        printf("Subscribe error: dictionary overflow\n");
        exit(1);
    }

    if (strlen(name) >= EVENT_NAME_LENGTH)
    {
        printf("Subscribe error: too long event name\n");
        exit(1);
    }

    /*
    TODO
    if (name-callback already exists)
    {
        //dont add same pair
    }
    */

    strncpy(event_dictionary[idx].name, name, EVENT_NAME_LENGTH);
    event_dictionary[idx].callback = callback;
    idx++;
}

void event_emit(const char *name)
{
    if (strlen(name) < EVENT_NAME_LENGTH)
    {
        if (!eor_is_full(&event_order_ring))
        {
            eor_push(&event_order_ring, name);
        }
        else
        {
            printf("Emit error: queue is full\n");
            exit(1);
        }
    }
    else
    {
        printf("Emit error: event name is too long\n");
        exit(1);
    }

}

static uint16_t event_find(event_name_t event, uint16_t search_idx)
{
    while (search_idx < EVENT_DICTIONARY_SIZE)
    {
        if (strcmp(event, event_dictionary[search_idx].name) == 0)
        {
            break;
        }
        search_idx++;
    }

    return search_idx;
}

void event_scheduler()
{
    static uint16_t search_idx = 0;
    static event_name_t event = "\0";

    if ( (strcmp(event, "\0") == 0) && !eor_is_empty(&event_order_ring))
    {
        eor_pop(&event_order_ring, event);
    }

    if (strcmp(event, "\0") != 0)
    {
        search_idx = event_find(event, search_idx);

        if (search_idx < EVENT_DICTIONARY_SIZE)
        {
            event_dictionary[search_idx].callback(NULL);
            search_idx++;
        }
        else
        {
            search_idx = 0;
            *event = '\0';
        }
    }
}
