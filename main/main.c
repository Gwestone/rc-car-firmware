#include <event.h>
#include <fs.h>
#include <http.h>
#include <wifi.h>
#include "driver/mcpwm.h"
#include "motor.h"

/* Example main */
void app_main(void)
{
   ESP_LOGI(TAG, "initiating the event loop");
   start_event_loop();
   ESP_LOGI(TAG, "initiating the file system");
   start_fs();
   ESP_LOGI(TAG, "initiating the wifi soft ap");
   start_wifi_softap();
   ESP_LOGI(TAG, "initiating the webserver");
   start_http_webserver();
   ESP_LOGI(TAG, "initializing motor control");
   start_motor();


//
//    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 19);
//
//    mcpwm_config_t pwm_config0;
//    pwm_config0.frequency = 50000   ;  //frequency
//    pwm_config0.cmpr_a = 0;      //duty cycle of PWMxA = 50.0%
//    pwm_config0.cmpr_b = 0;      //duty cycle of PWMxB = 50.0%
//    pwm_config0.counter_mode = MCPWM_UP_COUNTER; // Up-down counter (triangle wave)
//    pwm_config0.duty_mode = MCPWM_DUTY_MODE_0; // Active HIGH
//
//    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config0);    //Configure PWM0A & PWM0B with above settings
//
//    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_GEN_A, 60);

}
