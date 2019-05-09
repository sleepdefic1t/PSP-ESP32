
#include "gtest/gtest.h"

#include "psp_net.h"

#include <Arduino.h>
#include <WiFi.h>

// ArduinoJson Presets
#define ARDUINOJSON_USE_LONG_LONG 1
#define ARDUINOJSON_ENABLE_STD_STRING 1      // Enable 'std::string'
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 0  // disable 'String'
#include "ArduinoJson.h"


TEST(network, http_get) {
  const auto request = "http://167.114.29.45:4003/api/v2";

  // Get the 'request' response using HTTP
  const auto response = Ark::Platform::Network::HTTP::Get(request).c_str();

  if (WiFi.status() != WL_CONNECTED) {
    ASSERT_STREQ(response, "connection refused");
  } else {
    DynamicJsonDocument doc(256);
    deserializeJson(doc, response);
    ASSERT_EQ(404, doc["statusCode"]);
  };
}

TEST(network, http_post) {
  const auto request = "http://167.114.29.45:4003/api/v2/transactions";
  const auto txJson = "{\"transactions\":[]}";

  // Post the 'request' and 'txJson' for a response using HTTP
  const auto response = Ark::Platform::Network::HTTP::Post(request, txJson).c_str();

  if (WiFi.status() != WL_CONNECTED) {
    ASSERT_STREQ(response, "");
  } else {
    DynamicJsonDocument doc(256);
    deserializeJson(doc, response);
    ASSERT_EQ(422, doc["statusCode"]);
  };
}
