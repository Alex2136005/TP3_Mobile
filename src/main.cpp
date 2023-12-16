#include <Arduino.h>
#include <string>
#include "customUtils.h"
#include "config.h"
#include "wifiManager.h"
#include "../lib/RevolvairWebServer/src/revolvairWebServer.h"


customUtils utils;
String json;

WifiManager* wifiManager = nullptr;
RevolvairWebServer* webServer = nullptr;

void setup() {  
  const char* ssid = "Sly2021";
  const char* password = "jeveuxduwifi";

  wifiManager = new WifiManager(ssid, password);
  webServer = new RevolvairWebServer(new WebServer(80));
  wifiManager->initializeConnexion();
  webServer->initializeServer();
  
  Serial.begin(115200);
  json = utils.getJSONFromURL("https://staging.revolvair.org/api/revolvair/stations/cegep-de-ste-foy/");//config::URL_REVOLVAIR
  Serial.println("--------");
  Serial.println(json);
  Serial.println("--------");
}

void loop() {
  if(wifiManager->isConnected()){
    webServer->server->handleClient();
  }
  else
  {
    wifiManager->initializeConnexion();
  }
  delay(2);
}
