#include <event.h>

/* Example main */
void app_main(void)
{
   start_event_loop();
   create_iteration_event(10000);
}
