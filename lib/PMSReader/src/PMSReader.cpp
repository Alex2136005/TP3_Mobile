#include "PMSReader.h"

PMSReader::PMSReader(PMS& pms) {
    this->pms = &pms;
}
PMSReader::~PMSReader(){}

uint16_t PMSReader::getCurrentAirQualityReading(PMS::DATA& data )
{
 
    if (pms->read(data))
    {
        return data.PM_AE_UG_2_5; 
    }
    return std::numeric_limits<uint16_t>::max();
}


