#include "event_scheduler.h"
#include <stdio.h>

static void first_callback(void *param)
{
    printf("Check first_callback\n");
}

static void second_callback(void *param)
{
    printf("Check second_callback\n");
}

int main()
{
    event_subscribe("first", first_callback);
    event_subscribe("first", second_callback);
    event_subscribe("second", second_callback);
    event_emit("first");
    event_emit("second");

    while(1)
    {
        event_scheduler();
    }

    return 0;
}