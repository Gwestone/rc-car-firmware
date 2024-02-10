#include <event.h>
#include <fs.h>
#include <http.h>
#include <wifi.h>

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
}
