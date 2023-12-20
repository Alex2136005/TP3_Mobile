#include "revolvairWebServer.h"

const int redPin = 12;
const int greenPin = 13;
const int bluePin = 14;
uint8_t red, green, blue;

WebServer* RevolvairWebServer::server = nullptr;
FlashFileReader* RevolvairWebServer::fileReader = nullptr;
RevolvairWebServer::RevolvairWebServer(WebServer* webserver)
{  
    this->fileReader = new FlashFileReader();
    this->server = webserver;
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
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

String RevolvairWebServer::updateHtmlContentPage1(String niveau, String description, String hexColor) {
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


void RevolvairWebServer::initializeServer()
{
    HTTPClient http;
    http.begin("https://staging.revolvair.org/api/revolvair/aqi/aqhi");
    http.addHeader("Accept", "application/json");
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(5000);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();

    DynamicJsonDocument doc(4096);

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("Error parsing JSON: ");
        Serial.println(error.c_str());
        return;
    }

    //Change la lumière selon le value de la qualité d'aire (aqhi)
    int value = 52;
    String niveau = "";
    String description = "";
    String hexColor = "#ffffff";

    for (int i = 0; i < doc["ranges"].size(); ++i) {
        if (value < doc["ranges"][i]["max"]) {
            niveau = doc["ranges"][i]["label"].as<String>();
            description = doc["ranges"][i]["note"].as<String>();
            hexColor = doc["ranges"][i]["color"].as<String>();
            break;
        }
    }
    Serial.println(hexColor);
    //...

    //tout mettre dans RGBLedManager...
    long number;
    if(hexColor[0] == '#')  number = strtol(&hexColor[1], nullptr, 16);
    else number = strtol(&hexColor[0], nullptr, 16);
    red = number >> 16;
    green = number >> 8 & 0xFF;
    blue = number & 0xFF;
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

    String htmlContentNav = "<html>NavBar</html>";
    try
    { 
        htmlContentNav = fileReader->getFileByName("navbar.html");
    } catch (const std::runtime_error& e) {
      Serial.println("Exception: " + String(e.what()));
    }

    server->on("/", handleRoot);
    server->on("/qualitedelair", HTTP_GET, [this, htmlContentNav, niveau, description, hexColor](){
        server->send(200, "text/html", htmlContentNav + updateHtmlContentPage1(niveau, description, hexColor));
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
}
