#ifndef REVOLVAIR_WEBSERVER_H
#define REVOLVAIR_WEBSERVER_H

#include <WebServer.h>
#include <ESPmDNS.h>
#include "../../EPAScale/src/EPAScale.h"
#include "FlashFileReader.h"
#include <HTTPClient.h>
#include "../../RGBLedManager/src/RGBLedManager.h"

class RevolvairWebServer {
public:
    static WebServer* server;
    static FlashFileReader* fileReader;
    RevolvairWebServer(WebServer* webserver);
    RevolvairWebServer(EPAScale& scale); //pour les tests
    ~RevolvairWebServer();
    void initializeServer();
    void updateData(uint16_t pm_2_5);

private:
    EPAScale* epaScale;
    RevolvairAPI* api;
    static const int led = 13;
    static void handleRoot();
    static void handleNotFound();
    String updateHtmlContentPage1();
    String updateHtmlContentPage2();
    void handleUpdateRequest();
};

#endif



