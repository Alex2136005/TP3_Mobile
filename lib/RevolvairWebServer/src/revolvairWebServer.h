#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

class RevolvairWebServer{
    public:
    static WebServer* server;
    RevolvairWebServer(WebServer* webserver);
    ~RevolvairWebServer();
    void initializeServer();

    private:
    static const int led = 13;
    static void handleRoot();
    static void handleNotFound();
};