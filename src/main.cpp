
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ctype.h>
#include <string.h>
#include <Arduino.h>
#include "nvs_flash.h"

#include "sdkconfig.h"
#include "serial.h"
#include "analog.h"
#include "web.h"
#include "mpu.h"


extern "C" void app_main()
{
  Serial.begin(115200);
  pinMode(15,INPUT_PULLUP);
  pinMode(19,OUTPUT);
  digitalWrite(19,LOW);
  nvs_flash_init();

  mpu_init();

  xTaskCreate(serial_task, "serial_task", 2048, NULL, (tskIDLE_PRIORITY + 10), NULL);
  xTaskCreate(analog_task, "analog_task", 2048, NULL, (tskIDLE_PRIORITY + 2), NULL);
  //xTaskCreate(mpu_task, "mpu_task", 2048, NULL, (tskIDLE_PRIORITY + 2), NULL);
  xTaskCreatePinnedToCore(
                    mpu_task,   // Function to implement the task
                    "mpu_task", // Name of the task
                    10000,      // Stack size in words
                    NULL,       // Task input parameter
                    (tskIDLE_PRIORITY + 2),          // Priority of the task
                    NULL,       // Task handle.
                    1);  // Core where the task should run */

  //web_task(0);
  //mpu_task();

}
