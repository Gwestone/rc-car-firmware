#ifndef EVENT_SOURCE_H_
#define EVENT_SOURCE_H_

#include "esp_event.h"
#include "esp_timer.h"
#include <esp_log.h>
#include "constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_ITERATIONS_COUNT        10      // number of times the task iterates
#define TASK_PERIOD                  500     // period of the task loop in milliseconds

    ESP_EVENT_DECLARE_BASE(GLOBAL_EVENTS);         // declaration of the task events family

    enum {
        GLOBAL_ITERATION_EVENT                     // raised during an iteration of the loop within the task
    };

    void start_event_loop();
    void create_iteration_event(int iteration);

#ifdef __cplusplus
}
#endif

#endif // #ifndef EVENT_SOURCE_H_