#ifndef EVENT_ORDER_RING_H_
#define EVENT_ORDER_RING_H_

#include "event_scheduler.h"
#include <stdbool.h>
#include <string.h>

typedef struct
{
    event_name_t *buffer;
    uint16_t     size;
    uint16_t     current_size;
    uint16_t     in;
    uint16_t     out;
} event_order_ring_t;

inline static void eor_init(event_order_ring_t *ring, event_name_t *src_buf, uint16_t size)
{
    ring->buffer       = src_buf;
    ring->in           = 0;
    ring->out          = 0;
    ring->current_size = 0;
    ring->size         = size;
}

inline static void eor_push(event_order_ring_t *ring, char *name)
{
    strncpy((char *)ring->buffer[ring->in], name, strlen(name));
    ring->current_size++;

    ring->in++;
    if (ring->in >= ring->size)
    {
        ring->in = 0;
    }
}

inline static void eor_pop(event_order_ring_t *ring, event_name_t name)
{
    strncpy((char*)name, (char *)ring->buffer[ring->out],
            strlen((char *)ring->buffer[ring->out]));
    ring->current_size--;

    ring->out++;
    if (ring->out >= ring->size)
    {
        ring->out = 0;
    }
}

inline static bool eor_is_full(event_order_ring_t *ring)
{
    return ring->current_size >= ring->size;
}

inline static bool eor_is_empty(event_order_ring_t *ring)
{
    return ring->current_size == 0;
}

#endif /*EVENT_ORDER_RING_H_*/