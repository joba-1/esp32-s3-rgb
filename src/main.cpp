#include <Arduino.h>

// see http://wiki.fluidnc.com/en/hardware/ESP32-S3_Pin_Reference

#define LED_PIN    48
#define BTN_PIN     0


#include <rgb_circle.hpp>
rgb::NeoCircle<0xff, 0xff, false> circle(LED_PIN);


void setup() {
  ++circle;
  
  #if ARDUINO_USB_CDC_ON_BOOT == 1
    if (ESP_RST_POWERON == esp_reset_reason()) {
      delay(6500);
    }
  #endif

  Serial.begin(115200);
  delay(10);
  Serial.printf("Main start at %u with prio %u on core %d\n", millis(), uxTaskPriorityGet(NULL), xPortGetCoreID());

  pinMode(BTN_PIN, INPUT);

  Serial.println("Init done");
  Serial.flush();
  delay(10);

  // esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
}


void loop() {
  const uint32_t elapsed_led = 80;
  static uint32_t prev_led = 0;
  uint32_t now = millis();
  if (now - prev_led > elapsed_led) {
    prev_led = now;
    ++circle;
  }

  const uint32_t elapsed_print = 10000;
  static uint32_t prev_print = -elapsed_print;
  if (now - prev_print > elapsed_print) {
    prev_print = now;
    Serial.printf("Circling for %u seconds\n", now/1000);
  }

  if (!digitalRead(BTN_PIN)) {
    do { delay(10); } while (!digitalRead(BTN_PIN));
    ESP.restart();
  }

  esp_sleep_enable_timer_wakeup(10*1000);
  esp_light_sleep_start();
}
