#include "PMSReader.h"
extern PMS pms;
extern PMS::DATA data;
PMSReader::PMSReader()
{
}
uint16_t PMSReader::getCurrentAirQualityReading()
{
    if (pms.read(data))
    {
        return data.PM_AE_UG_2_5;
    }
    throw std::runtime_error("Failed to read air quality data");
}


