#include <PMS.h>
#include <Arduino.h>
 
class PMSReader
{
    private:
        PMS* pms;
    public:
        PMSReader(PMS& pms);
        ~PMSReader();
        uint16_t getCurrentAirQualityReading(PMS::DATA& data);
};