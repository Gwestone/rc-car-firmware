#include "fs.h"

#include <sys/_default_fcntl.h>

void start_fs() {

    ESP_LOGI(TAG, "start fs test!");
    esp_vfs_spiffs_conf_t spiffsConf = {
        .base_path = "/storage",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };
    esp_err_t res = esp_vfs_spiffs_register(&spiffsConf);

    if (res != ESP_OK) {
        ESP_LOGE(TAG, "failed to init spiffs: %s", esp_err_to_name(res));
        return;
    }

    ESP_LOGI(TAG, "Performing SPIFFS check.");
    res = esp_spiffs_check(spiffsConf.partition_label);
    if (res != ESP_OK) {
        ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(res));
        return;
    } else {
        ESP_LOGI(TAG, "SPIFFS_check() successful");
    }

    size_t total = 0, used = 0;
    res = esp_spiffs_info(spiffsConf.partition_label, &total, &used);
    if (res != ESP_OK) {
        ESP_LOGE(TAG, "failed to get data from spiffs: %s", esp_err_to_name(res));
    } else {
        ESP_LOGI(TAG, "partition size total: %d, used: %d", total, used);
    }

    //code for reading a file
    // ESP_LOGI(TAG, "start file check");
    // struct stat st;
    // if (stat("/storage/test.txt", &st) != 0) {
    //     ESP_LOGE(TAG, "file test.txt doesnt exists, exit the program!");
    //     return;
    // }
    // ESP_LOGI(TAG, "success file check, next read check");
    //
    // ESP_LOGI(TAG, "start testing ffs");
    // FILE* f = fopen("/storage/test.txt", "r");
    // if (f == NULL) {
    //     ESP_LOGE(TAG, "test failed to open file for reading");
    //     return;
    // }

    // char line[128];
    // fgets(line, sizeof(line), f);
    // fclose(f);
    // printf("%s\n", line);
}
