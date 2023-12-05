#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

class WifiManager{
    public:
    WifiManager(WebServer* server);
    ~WifiManager();
    static WebServer* server;

    private:
    static const int led = 13;


    static void handleRoot();
    static void handleNotFound();
    static void initialize();

};