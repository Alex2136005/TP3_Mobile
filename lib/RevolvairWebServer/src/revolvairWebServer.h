#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "FS.h"
#include "SPIFFS.h"
#include "../../customUtils.h"
#include "../../../src/config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

class RevolvairWebServer{
    public:
    static WebServer* server;
    RevolvairWebServer(WebServer* webserver);
    ~RevolvairWebServer();
    void initializeServer();
    void setPM25(uint16_t pm_2_5);

    private:
    static const int led = 13;
    String pm_2_5 = "VEILLEZ CONNECTER LE CAPTEUR DE PARTICULE";
    static void handleRoot();
    static void handleNotFound();
    String updateHtmlContentPage1(String niveau, String description, String hexColor);
    String updateHtmlContentPage2();
};