#include "http.h"

// Asynchronous response data structure
struct async_resp_arg
{
    httpd_handle_t hd; // Server instance
    int fd;            // Session socket file descriptor
};

/* Our URI handler function to be called during GET /uri request */
esp_err_t get_handler(httpd_req_t *req)
{
    /* Send a simple response */
    const char resp[] = "URI GET Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

/* Our URI handler function to be called during POST /uri request */
esp_err_t post_handler(httpd_req_t *req)
{
    /* Destination buffer for content of HTTP POST request.
     * httpd_req_recv() accepts char* only, but content could
     * as well be any binary data (needs type casting).
     * In case of string data, null termination will be absent, and
     * content length would give length of string */
    char content[100];

    /* Truncate if content length larger than the buffer */
    size_t recv_size = MIN(req->content_len, sizeof(content));

    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0) {  /* 0 return value indicates connection closed */
        /* Check if timeout occurred */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            /* In case of timeout one can choose to retry calling
             * httpd_req_recv(), but to keep it simple, here we
             * respond with an HTTP 408 (Request Timeout) error */
            httpd_resp_send_408(req);
        }
        /* In case of error, returning ESP_FAIL will
         * ensure that the underlying socket is closed */
        return ESP_FAIL;
    }

    /* Send a simple response */
    const char resp[] = "URI POST Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t ws_handler(httpd_req_t *req) {
    if (req->method == HTTP_GET) {
        ESP_LOGI(TAG, "Handshake done, the new connection was opened");
        return ESP_OK;
    }

    uint8_t* buf = NULL;

    httpd_ws_frame_t wsFrame;
    wsFrame.payload = NULL;
    memset(&wsFrame, 0, sizeof(httpd_ws_frame_t));
    wsFrame.type = HTTPD_WS_TYPE_TEXT;

    esp_err_t err = httpd_ws_recv_frame(req, &wsFrame, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "httpd_ws_recv_frame failed to get frame len with %d", err);
        return err;
    }
    ESP_LOGI(TAG, "Successfully recived message from client with length: %d", wsFrame.len);
    if (wsFrame.len) {
        buf = calloc(1, wsFrame.len + 1);
        wsFrame.payload = buf;

        err = httpd_ws_recv_frame(req, &wsFrame, wsFrame.len);
        if (err != ESP_OK) {
            ESP_LOGI(TAG, "Cant parse received message: %d", err);
            free(buf);
            return err;
        }
        ESP_LOGI(TAG, "Got packet with message: %s", wsFrame.payload);
        for (int i = 0; i < wsFrame.len; ++i) {

        }
    }
    ESP_LOGI(TAG, "Packet type: %d", wsFrame.type);
    // if (wsFrame.type == HTTPD_WS_TYPE_TEXT && strcmp((char*)wsFrame.payload,"Trigger async") == 0) {
    //     free(buf);
    //     return trigger_async_send(req->handle, req);
    // }

    err = httpd_ws_send_frame(req, &wsFrame);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "httpd_ws_send_frame failed with %d", err);
    }
    free(buf);
    return ESP_OK;
}

/* URI handler structure for GET /uri */
httpd_uri_t uri_ws = {
    .uri      = "/ws",
    .method   = HTTP_GET,
    .handler  = ws_handler,
    .handle_ws_control_frames = false,
    .supported_subprotocol = "chat",
    .is_websocket = true,
    .user_ctx = NULL
};

/* URI handler structure for GET /uri */
httpd_uri_t uri_get = {
    .uri      = "/uri",
    .method   = HTTP_GET,
    .handler  = get_handler,
    .user_ctx = NULL
};

/* URI handler structure for POST /uri */
httpd_uri_t uri_post = {
    .uri      = "/uri",
    .method   = HTTP_POST,
    .handler  = post_handler,
    .user_ctx = NULL
};

/* Function for starting the webserver */
httpd_handle_t start_http_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_post);
        httpd_register_uri_handler(server, &uri_ws);
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

/* Function for stopping the webserver */
void stop_http_webserver(httpd_handle_t server)
{
    if (server) {
        /* Stop the httpd server */
        httpd_stop(server);
    }
}