#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void)
{
    while (true) {
    }

    vTaskDelete(NULL);
}

#ifdef __cplusplus
}
#endif