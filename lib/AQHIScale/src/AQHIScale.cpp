#include "AQHIScale.h"

AQHIScale::AQHIScale()
{
    this->level = "";
    this->description = "";
    this->hexColor = "";
}

void AQHIScale::setLevel(String level){
    this->level = level;
}
void AQHIScale::setDescription(String description){
    this->description = description;
}
void AQHIScale::setHexColor(String hexColor){
    this->hexColor = hexColor;
}

