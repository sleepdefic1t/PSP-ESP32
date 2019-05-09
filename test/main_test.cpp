
#include "gtest/gtest.h"

#include <Arduino.h>

#include <cstring>

// Connecting to WiFi is optional for testing.
#include <WiFi.h>
// This is the WiFi network you'd like your board to connect to.
const char* ssid = "yourSSID";
const char* password = "yourWiFiPassword";

/**/

// Set Dummy Time for testing board
#include <sys/time.h>
void setDummyTime() {
  // set board time to: 21 March 2019(in seconds)
  // 2 years after Mainnet launch.
  struct timeval tv;
  tv.tv_sec = 1553173200ull; 
  settimeofday(&tv, NULL);
};

/**/


void setup() {
  Serial.begin(115200);

  // if ssid and passwd set
  if (strcmp(ssid, "yourSSID") != 0 && strcmp(password, "yourWiFiPassword") != 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    };
    Serial.println();
    Serial.println(WiFi.localIP());
  };

  setDummyTime();

  testing::InitGoogleTest();

  auto __attribute__((unused)) run = RUN_ALL_TESTS();
}

void loop() {
  // do nothing
  esp_deep_sleep_start();
}
