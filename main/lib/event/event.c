#include "event.h"

esp_event_loop_handle_t global_loop;

/* Event source task related definitions */
ESP_EVENT_DEFINE_BASE(GLOBAL_EVENTS);

static void task_iteration_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    switch (id) {
        case GLOBAL_ITERATION_EVENT:
                const int iteration = *((int*) event_data);
                ESP_LOGI(TAG, "handling %s:%s from global_event_loop, iteration %d", base, "GLOBAL_ITERATION_EVENT", iteration);
            break;
        case GLOBAL_MOVEMENT_EVENT:
                char direction = *((char*)event_data);
                ESP_LOGI(TAG, "handling %s:%s from global_event_loop, direction %c", base, "GLOBAL_MOVEMENT_EVENT", direction);
            break;
        default:
            ESP_LOGE(TAG, "cant handle event %s:%s from global_event_loop, with data address: %p", base, "UNDEFINDED", event_data);
            break;
    }
}

static void task_event_source(void* args)
{
    for(int iteration = 1; iteration <= TASK_ITERATIONS_COUNT; iteration++) {

        ESP_LOGI(TAG, "posting %s:%s to loop_with_task, iteration %d out of %d", GLOBAL_EVENTS, "TASK_ITERATION_EVENT",
                iteration, TASK_ITERATIONS_COUNT);

        ESP_ERROR_CHECK(esp_event_post_to(global_loop, GLOBAL_EVENTS, GLOBAL_ITERATION_EVENT, &iteration, sizeof(iteration), portMAX_DELAY));

        vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));
    }

    vTaskDelay(pdMS_TO_TICKS(TASK_PERIOD));

    ESP_LOGI(TAG, "deleting task event source");

    vTaskDelete(NULL);
}

void start_event_loop() {
    ESP_LOGI(TAG, "setting up");

    esp_event_loop_args_t loop_with_task_args = {
        .queue_size = 5,
        .task_name = "loop_task",
        .task_priority = uxTaskPriorityGet(NULL),
        .task_stack_size = 3072,
        .task_core_id = tskNO_AFFINITY
    };

    // Create the event loops
    ESP_ERROR_CHECK(esp_event_loop_create(&loop_with_task_args, &global_loop));

    // Register the handler for task iteration event. Notice that the same handler is used for handling event on different loops.
    // The loop handle is provided as an argument in order for this example to display the loop the handler is being run on.
    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(global_loop, GLOBAL_EVENTS, ESP_EVENT_ANY_ID, task_iteration_handler, global_loop, NULL));

    // Create the event source task
    // TaskHandle_t task_event_source_hdl;
    // ESP_LOGI(TAG, "starting event source");
    // xTaskCreate(task_event_source, "task_event_source", 3072, NULL, uxTaskPriorityGet(NULL) + 1, &task_event_source_hdl);
}

void create_iteration_event(const int iteration) {
    ESP_ERROR_CHECK(esp_event_post_to(global_loop, GLOBAL_EVENTS, GLOBAL_ITERATION_EVENT, &iteration, sizeof(iteration), portMAX_DELAY));
}

void create_movement_event(const enum direction_t direction) {
    ESP_ERROR_CHECK(esp_event_post_to(global_loop, GLOBAL_EVENTS, GLOBAL_MOVEMENT_EVENT, &direction, sizeof(direction), portMAX_DELAY));
}