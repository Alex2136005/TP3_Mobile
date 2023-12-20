#include <WebServer.h>
#include <ESPmDNS.h>
#include "../../RevolvairAPI/src/RevlovairAPI.h"
#include <ArduinoJson.h>
#include "FlashFileReader.h"
#include "../../customUtils.h"
#include <HTTPClient.h>
#include "../../RGBLedManager/src/RGBLedManager.h"
class RevolvairWebServer{
    public:
    static WebServer* server;
    static FlashFileReader* fileReader;
    RevolvairWebServer(WebServer* webserver);
    ~RevolvairWebServer();
    void initializeServer();
    void setPM25(uint16_t pm_2_5);

    private:
    String niveau, description, hexColor;
    static DynamicJsonDocument doc;
    RevolvairAPI* api;
    static const int led = 13;
    String pm_2_5 = "VEILLEZ CONNECTER LE CAPTEUR DE PARTICULE";
    static void handleRoot();
    static void handleNotFound();
    String updateHtmlContentPage1();
    String updateHtmlContentPage2();
    void updateValues();
};