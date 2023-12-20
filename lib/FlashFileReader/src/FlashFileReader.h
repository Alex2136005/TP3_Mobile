#include "FS.h"
#include "SPIFFS.h"
#include <iostream>
#include <stdexcept>


class FlashFileReader
{
private:

public:
    FlashFileReader();
    ~FlashFileReader();
    String getFileByName(String name);
};

