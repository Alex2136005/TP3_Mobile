// Installer GCC : choco install mingw 
// lancer les tests natifs : pio test -e native

#include <unity.h>

void setUp(void) {
// set stuff up here
}

// void tearDown(void) {
// // clean stuff up here
// }

// void test_function_scale_getColorForPM25Value_When_PM_is_Low(void) {
//     TEST_ASSERT_EQUAL(1, scale.getColorForPM25Value(5));
// }

// void test_function_scale_getColorForPM25Value_When_PM_is_Average(void) {
//     TEST_ASSERT_EQUAL(2, scale.getColorForPM25Value(15));
// }

void test_function_scale_getColorForPM25Value_When_PM_is_High(void) {
    TEST_ASSERT_EQUAL(3, 3);
}

void process() {
    UNITY_BEGIN();
    // RUN_TEST(test_function_scale_getColorForPM25Value_When_PM_is_Low);
    // RUN_TEST(test_function_scale_getColorForPM25Value_When_PM_is_Average);
    RUN_TEST(test_function_scale_getColorForPM25Value_When_PM_is_High);
    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    process();
}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv) {
    //process();
    return 0;
}

#endif

