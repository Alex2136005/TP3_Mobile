#include <unity.h>
void setup() {
}

void loop() {
}

void test1(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(test1);
    UNITY_END();
}
