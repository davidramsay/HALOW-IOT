#include <WiFi.h>

const char* adminSsid = "ESP32S3_ADMIN_AP";
const char* adminPassword = "h@l0w";   // must be >= 8 chars

void setup() {
  Serial.begin(115200);

  Serial.println("Starting WiFi Access Point...");

  bool result = WiFi.softAP(adminSsid, adminPassword);

  if (result) {
    Serial.println("Access Point started");
    Serial.print("SSID: ");
    Serial.println(adminSsid);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP start failed");
  }
}

void loop() {
  // nothing required
}
