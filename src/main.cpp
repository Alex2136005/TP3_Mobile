#include <Arduino.h>
#include "wifiManager.h"
WifiManager* wifiManager = nullptr;
void setup() {
  wifiManager = new WifiManager(new WebServer(80));
}
void loop() {
  wifiManager->server->handleClient();
  delay(2);
}
