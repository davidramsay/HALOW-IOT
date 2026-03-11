#include <FS.h>
#include <LittleFS.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include "FSWebServer.h"  //reference https://github.com/cotestatnt/esp-fs-webserver


const char* adminSsid = "ESP32S3_AP";
const char* adminPassword = "h@l0wHost";   // must be >= 8 chars


#define FILESYSTEM LittleFS
FSWebServer server(LittleFS, 80, "esphost");

////////////////////////////////  Filesystem  /////////////////////////////////////////
bool startFilesystem() {
  if (FILESYSTEM.begin()){
    server.printFileList(LittleFS, "/", 1, Serial);   
    return true;
  }
  else {
      Serial.println("ERROR on mounting filesystem. It will be reformatted!");
      FILESYSTEM.format();
      ESP.restart();
  }
  return false;
}

////////////////////////////////  SETUP  /////////////////////////////////////////
void setup() 
{
   // start serial line and print notification
  Serial.begin(115200);
  Serial.println("Starting WiFi Access Point...");

  // FILESYSTEM INIT
  startFilesystem();

  // Try to connect to WiFi with previous credentials, start AP if not connected after timeout
  if (!server.startWiFi(10000)) {
    Serial.println("\nWiFi not connected! Starting AP mode...");
    server.startCaptivePortal(adminSsid, adminPassword, "/setup");
  }

  // Enable ACE FS file web editor and add FS info callback function.
  // leaving this in so I can add in other files later :)
  server.enableFsCodeEditor();
  
  // Start server
  server.begin();
  Serial.print(F("ESP Web Server started on IP Address: "));
  Serial.println(server.getServerIP());
  Serial.println(F(
    "This is \"handleFormData.ino\" example.\n"
    "Open /setup page to configure optional parameters.\n"
    "Open /edit page to view, edit or upload example or your custom webserver source files."
  ));
}

void loop() 
{
  // Handle client requests
  server.run();
  
  // delay to ease compute consumption
  delay(10);  
}
