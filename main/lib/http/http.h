#ifndef HTTP_H
#define HTTP_H
#include <esp_http_server.h>
#include <esp_err.h>
#include "constants.h"
#include <esp_log.h>

httpd_handle_t start_http_webserver(void);
void stop_http_webserver(httpd_handle_t server);

#endif //HTTP_H
