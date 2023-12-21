#include "test_pm25_label.h"
#include "test_RGB.h"

void setup() 
{
    delay(2000);
    UNITY_BEGIN();
    process_test_RGB();
    RUN_TEST(test_function_getLabelFromPM25);
    UNITY_END();
}

void loop() {

}
