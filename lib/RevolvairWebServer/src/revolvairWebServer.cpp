#include "revolvairWebServer.h"

const int redPin = 12;
const int greenPin = 13;
const int bluePin = 14;
uint8_t red, green, blue;
RGBLedManager* ledManager = new RGBLedManager(redPin, greenPin, bluePin);
DynamicJsonDocument RevolvairWebServer::doc(4096);

WebServer* RevolvairWebServer::server = nullptr;
FlashFileReader* RevolvairWebServer::fileReader = nullptr;
RevolvairWebServer::RevolvairWebServer(WebServer* webserver)
{  
    this->fileReader = new FlashFileReader();
    this->server = webserver;
    this->niveau = "";
    this->description = "";
    this->hexColor = "";
    Serial2.begin(9600);
    api = new RevolvairAPI();
}

void RevolvairWebServer::handleNotFound(){
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
        htmlContentPage1.replace("%PM_2_5%", String(pm_2_5));
        htmlContentPage1.replace("%NIVEAU%", niveau);
        htmlContentPage1.replace("%DESCRIPTION%", description);
        htmlContentPage1.replace("%HEX_COLOR%", hexColor);

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
        htmlContentPage2.replace("%MAC_ADDRESS%", WifiManager::getMacAddress());
        htmlContentPage2.replace("%DEVICE_ID%", WifiManager::getUniqueId());
        htmlContentPage2.replace("%WIFI_SSID%",  WifiManager::getSSID());
        htmlContentPage2.replace("%WIFI_RSSI%",  WifiManager::getWifiRSSI());
        return htmlContentPage2;

    } catch (const std::runtime_error& e) 
    {
        Serial.println("Exception: " + String(e.what()));
    }
    return "<html> Une erreur est survenue. </html>";
}

void RevolvairWebServer::handleUpdateRequest() {
    String jsonResponse = "{";
    jsonResponse += "\"pm_2_5\":\"" + pm_2_5 + "\",";
    jsonResponse += "\"niveau\":\"" + niveau + "\",";
    jsonResponse += "\"description\":\"" + description + "\",";
    jsonResponse += "\"hexColor\":\"" + hexColor + "\"";
    jsonResponse += "}";

    server->sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
    server->sendHeader("Pragma", "no-cache");
    server->sendHeader("Expires", "0");

    server->send(200, "application/json", jsonResponse);
}

void RevolvairWebServer::initializeServer()
{
    String payload = api->getJSONFromURL("https://staging.revolvair.org/api/revolvair/aqi/aqhi");

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
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
        handleUpdateRequest();
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage1());
    });
     server->on("/informationdelappareil", HTTP_GET, [this, htmlContentNav](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage2());
    });
    server->onNotFound(handleNotFound);
    server->begin();

    Serial.println("HTTP server started");
}

void RevolvairWebServer::setPM25(uint16_t pm_2_5)
{
    this->pm_2_5 = String(pm_2_5);
    updateValues();
}

void RevolvairWebServer::updateValues()
{
    //Change la lumière selon le value de la qualité d'aire (aqhi)
    String niveau = "";
    String description = "";
    String hexColor = "#ffffff";

    for (int i = 0; i < doc["ranges"].size(); ++i) {
        if (this->pm_2_5.toInt() < doc["ranges"][i]["max"]) {
            niveau = doc["ranges"][i]["label"].as<String>();
            description = doc["ranges"][i]["note"].as<String>();
            hexColor = doc["ranges"][i]["color"].as<String>();
            break;
        }
    }

    this->niveau = niveau;
    this->description = description;
    this->hexColor = hexColor;

    ledManager->setLed(String(hexColor.c_str()));
}