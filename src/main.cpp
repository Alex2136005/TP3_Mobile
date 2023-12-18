#include <Arduino.h>
#include <string>
#include "config.h"
#include "wifiManager.h"
#include "../lib/RevolvairWebServer/src/revolvairWebServer.h"

#include <PMS.h>
PMS pms(Serial2);
PMS::DATA data;

WifiManager* wifiManager = nullptr;
RevolvairWebServer* webServer = nullptr;

unsigned long previousMillis = 0;
const long interval = 5000;

void PMManager();

void setup() {  
  const char* ssid = config::WIFI_NAME;
  const char* password = config::WIFI_PASSWORD;

  wifiManager = new WifiManager(ssid, password);
  webServer = new RevolvairWebServer(new WebServer(80));
  wifiManager->initializeConnexion();
  webServer->initializeServer();
  
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop() {
  if(wifiManager->isConnected()){
    webServer->server->handleClient();
  }
  else
  {
    wifiManager->initializeConnexion();
  }
  //Appelé tout les 5 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    if (pms.read(data))
    {
      previousMillis = currentMillis;
      PMManager();
    }
  }
  // if (pms.read(data))
  // {
  //   Serial.print("PM 1.0 (ug/m3): ");
  //   Serial.println(data.PM_AE_UG_1_0);
  //   Serial.print("PM 2.5 (ug/m3): "); 
  //   Serial.println(data.PM_AE_UG_2_5);
  //   Serial.print("PM 10.0 (ug/m3): ");
  //   Serial.println(data.PM_AE_UG_10_0);
  //   Serial.println();
  // }
  delay(2);
}

void PMManager() {
  //gestion du capteur qualité d'aire
  webServer->setPM25(data.PM_AE_UG_2_5);
  Serial.print("PM 2.5 (ug/m3): "); 
  Serial.println(data.PM_AE_UG_2_5);
  Serial.println();
}
