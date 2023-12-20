#ifndef PMS_READER_H
#define PMS_READER_H

#include <PMS.h>
#include <Arduino.h>

class PMSReader {
private:
    PMS* pms;

public:
    PMSReader(PMS& pms);
    ~PMSReader();
    uint16_t getCurrentAirQualityReading(PMS::DATA& data);
};

#endif // PMS_READER_H
