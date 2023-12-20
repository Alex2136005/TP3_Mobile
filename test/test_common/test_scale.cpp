// Installer GCC : choco install mingw 
// lancer les tests natifs : pio test -e native

#include <unity.h>

void setUp(void) 
{
}
void tearDown(void) {
}

// void test_function_scale_getColorForPM25Value_When_PM_is_Low(void) {
//     TEST_ASSERT_EQUAL(1, scale.getColorForPM25Value(5));
// }

// void test_function_scale_getColorForPM25Value_When_PM_is_Average(void) {
//     TEST_ASSERT_EQUAL(2, scale.getColorForPM25Value(15));
// }

void test_function_getAQILabelFromPM25(float pm25Value) 
{

    TEST_ASSERT_EQUAL("Bon", );
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(test_function_getAQILabelFromPM25(1.0F));
    UNITY_END();
}


