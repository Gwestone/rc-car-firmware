#include "motor.h"

#define MOTOR_LEFT_1_GPIO_PIN GPIO_NUM_18
#define MOTOR_RIGHT_1_GPIO_PIN GPIO_NUM_19

#define MOTOR_LEFT_2_GPIO_PIN GPIO_NUM_21
#define MOTOR_RIGHT_2_GPIO_PIN GPIO_NUM_22

static void task_movement_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    switch (id) {
        case GLOBAL_MOVEMENT_EVENT:
            char direction = *((char*)event_data);
            switch (direction) {
                case 'U':
                    ESP_LOGI(TAG, "[Moving up]");
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 100);
                    gpio_set_level(MOTOR_LEFT_1_GPIO_PIN, 1);
                    gpio_set_level(MOTOR_LEFT_2_GPIO_PIN, 1);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 0);
                    gpio_set_level(MOTOR_LEFT_1_GPIO_PIN, 0);
                    gpio_set_level(MOTOR_LEFT_2_GPIO_PIN, 0);
                    break;
                case 'D':
                    ESP_LOGI(TAG, "[Moving down]");
                    gpio_set_level(MOTOR_RIGHT_1_GPIO_PIN, 1);
                    gpio_set_level(MOTOR_RIGHT_2_GPIO_PIN, 1);
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, 100);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_GEN_A, 0);
                    gpio_set_level(MOTOR_RIGHT_1_GPIO_PIN, 0);
                    gpio_set_level(MOTOR_RIGHT_2_GPIO_PIN, 0);
                    break;
                case 'R':
                    ESP_LOGI(TAG, "[Moving right]");
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 100);
                    gpio_set_level(MOTOR_LEFT_1_GPIO_PIN, 1);
                    gpio_set_level(MOTOR_RIGHT_2_GPIO_PIN, 1);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 0);
                    gpio_set_level(MOTOR_LEFT_1_GPIO_PIN, 0);
                    gpio_set_level(MOTOR_RIGHT_2_GPIO_PIN, 0);
                    break;
                case 'L':
                    ESP_LOGI(TAG, "[Moving left]");
                    //                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 100);
                    gpio_set_level(MOTOR_LEFT_2_GPIO_PIN, 1);
                    gpio_set_level(MOTOR_RIGHT_1_GPIO_PIN, 1);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
//                    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 0);
                    gpio_set_level(MOTOR_LEFT_2_GPIO_PIN, 0);
                    gpio_set_level(MOTOR_RIGHT_1_GPIO_PIN, 0);
                    break;
                default:
                    ESP_LOGI(TAG, "[Unknown direction]");
                    break;
            }
            break;
        default:
            ESP_LOGE(TAG, "cant handle movement event %s:%s from movement handler, with data address: %p", base, "UNDEFINDED", event_data);
            break;
    }
}

void start_motor(){
    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(global_loop, GLOBAL_EVENTS, GLOBAL_MOVEMENT_EVENT,
                                                             task_movement_handler, global_loop, NULL));

    gpio_config_t io_conf1 = {
            .pin_bit_mask = (1ULL << MOTOR_LEFT_1_GPIO_PIN),
            .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&io_conf1);

    gpio_config_t io_conf2 = {
            .pin_bit_mask = (1ULL << MOTOR_RIGHT_1_GPIO_PIN),
            .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&io_conf2);

    gpio_config_t io_conf3 = {
            .pin_bit_mask = (1ULL << MOTOR_LEFT_2_GPIO_PIN),
            .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&io_conf3);

    gpio_config_t io_conf4 = {
            .pin_bit_mask = (1ULL << MOTOR_RIGHT_2_GPIO_PIN),
            .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&io_conf4);

//    gpio_set_direction(18, GPIO_MODE_OUTPUT);
//    gpio_set_direction(19, GPIO_MODE_OUTPUT);
//    gpio_set_direction(21, GPIO_MODE_OUTPUT);
//    gpio_set_direction(22, GPIO_MODE_OUTPUT);

//    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 19);
//    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, 20);
//
//    mcpwm_config_t pwm_config0;
//    pwm_config0.frequency = 50000   ;  //frequency
//    pwm_config0.cmpr_a = 0;      //duty cycle of PWMxA = 50.0%
//    pwm_config0.cmpr_b = 0;      //duty cycle of PWMxB = 50.0%
//    pwm_config0.counter_mode = MCPWM_UP_COUNTER; // Up-down counter (triangle wave)
//    pwm_config0.duty_mode = MCPWM_DUTY_MODE_0; // Active HIGH
//
//    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
//    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
}

