#include <Arduino.h>

// see http://wiki.fluidnc.com/en/hardware/ESP32-S3_Pin_Reference

#define LED_PIN    48


#include <rgb_circle.hpp>
RTC_DATA_ATTR rgb::NeoCircle<0xff, 0xff, false> circle(LED_PIN);


void setup() {
  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
    circle.init();
  }

  ++circle;
  esp_sleep_enable_timer_wakeup(80*1000);
  esp_deep_sleep_start();
}


void loop() {
}
