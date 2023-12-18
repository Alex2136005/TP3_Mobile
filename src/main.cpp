#include <Arduino.h>
#include "wifiManager.h"
#include "../lib/RevolvairWebServer/src/revolvairWebServer.h"

WifiManager* wifiManager = nullptr;
RevolvairWebServer* webServer = nullptr;

void setup() {
  const char* ssid = "Fizz_Martin";
  const char* password = "Jumeaux_12345";

  wifiManager = new WifiManager(ssid, password);
  webServer = new RevolvairWebServer(new WebServer(80));
  wifiManager->initializeConnexion();
  webServer->initializeServer();

}
void loop() 
{
  if(wifiManager->isConnected()){
    webServer->server->handleClient();
  }
  else
  {
    wifiManager->initializeConnexion();
  }
  delay(2);
}
