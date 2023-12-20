#include "FlashFileReader.h"    

FlashFileReader::FlashFileReader()
{
    if(!SPIFFS.begin(true))
    {
      Serial.print("\n SPIFFS mount failed ! \n");
      return;
    }
    Serial.print("\n SPIFFS mounted successfully! \n");
}

String FlashFileReader::getFileByName(String name)
{
    
    File file = SPIFFS.open("/" + name, "r");
    if (!file) 
    {
        throw std::runtime_error("Le fichier est introuvable.");
    }
    String retval = file.readString();
    file.close();
    return retval;
}
