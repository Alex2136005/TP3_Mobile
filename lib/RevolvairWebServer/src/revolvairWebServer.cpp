#include "revolvairWebServer.h"

const int redPin = 12;
const int greenPin = 13;
const int bluePin = 14;
uint8_t red, green, blue;
RGBLedManager* ledManager = new RGBLedManager(redPin, greenPin, bluePin);

WebServer* RevolvairWebServer::server = nullptr;
FlashFileReader* RevolvairWebServer::fileReader = nullptr;
RevolvairWebServer::RevolvairWebServer(WebServer* webserver)
{  
    
    this->fileReader = new FlashFileReader();
    this->server = webserver;
    this->api = new RevolvairAPI();
}

RevolvairWebServer::RevolvairWebServer(EPAScale& scale)
{  
    
    this->fileReader = new FlashFileReader();
    this->api = new RevolvairAPI();
    this->epaScale = &scale;
}

void RevolvairWebServer::handleNotFound()
{
    digitalWrite(led, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += (server->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";
    for (uint8_t i = 0; i < server->args(); i++) {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }
    server->send(404, "text/plain", message);
    digitalWrite(led, 0);
}


void RevolvairWebServer::handleRoot(){
    digitalWrite(led, 1);
    try 
    {
        String htmlContent = fileReader->getFileByName("index.html");
        server->send(200, "text/html", htmlContent);
    } catch (const std::runtime_error& e) {
        Serial.println("Exception: " + String(e.what()));
    }

    digitalWrite(led, 0);
}

String RevolvairWebServer::updateHtmlContentPage1() {
    try 
    {
        String htmlContentPage1 = fileReader->getFileByName("airQuality.html");
        htmlContentPage1.replace("%PM_2_5%", this->epaScale->getLastScanResult());
        htmlContentPage1.replace("%NIVEAU%", this->epaScale->getLevel());
        htmlContentPage1.replace("%DESCRIPTION%", this->epaScale->getDescription());
        htmlContentPage1.replace("%HEX_COLOR%", this->epaScale->getHexColor());

        return htmlContentPage1;
    } catch (const std::runtime_error& e) 
    {
        Serial.println("Exception: " + String(e.what()));
    }
    return "<html> Une erreur est survenue. </html>";
}

String RevolvairWebServer::updateHtmlContentPage2() 
{
    try 
    {
        String htmlContentPage2 = fileReader->getFileByName("deviceInfo.html");
        htmlContentPage2.replace("%MAC_ADDRESS%", WifiController::getMacAddress());
        htmlContentPage2.replace("%DEVICE_ID%", WifiController::getUniqueId());
        htmlContentPage2.replace("%WIFI_SSID%",  WifiController::getSSID());
        htmlContentPage2.replace("%WIFI_RSSI%",  WifiController::getWifiRSSI());
        return htmlContentPage2;

    } catch (const std::runtime_error& e) 
    {
        Serial.println("Exception: " + String(e.what()));
    }
    return "<html> Une erreur est survenue. </html>";
}

void RevolvairWebServer::initializeServer()
{

    DynamicJsonDocument temp(4096);
    String payload = api->getJSONFromURL("https://staging.revolvair.org/api/revolvair/aqi/usepa/fr");
    DeserializationError error = deserializeJson(temp, payload);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
    }else
    {
        String jsonString;
        serializeJson(temp, jsonString);

        // Print the string
        Serial.println(jsonString);
        this->epaScale = new EPAScale(temp);
        Serial2.begin(9600);
    }

    Serial.println("Mac ID : "+String(WiFi.macAddress()));
    Serial.println("Wifi SSID : "+String(WiFi.SSID()));
    Serial.println("Wifi RSSI : "+String(WiFi.RSSI()));
    Serial.println("Device Id : "+String(ESP.getEfuseMac()));

    String htmlContentNav = "<html>NavBar</html>";
    try
    { 
        htmlContentNav = fileReader->getFileByName("navbar.html");
    } catch (const std::runtime_error& e) {
      Serial.println("Exception: " + String(e.what()));
    }

    server->on("/", handleRoot);
    server->on("/qualitedelair", HTTP_GET, [this, htmlContentNav](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage1());
    });
     server->on("/informationdelappareil", HTTP_GET, [this, htmlContentNav](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage2());
    });
    server->onNotFound(handleNotFound);
    server->begin();

    Serial.println("HTTP server started");
}

void RevolvairWebServer::updateData(uint16_t pm_2_5)
{
    epaScale->updateInfos(String(pm_2_5));
    ledManager->setLed(this->epaScale->getRGBColorFromPM25(pm_2_5));
}
