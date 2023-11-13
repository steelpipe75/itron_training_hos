#include "gmock/gmock.h"
#include "gtest/gtest.h"

extern "C" int get_eat_count(int num);
extern "C" void wait_eating(void);

TEST(SampleTest, EatCount) {
    wait_eating();
    EXPECT_EQ(get_eat_count(2), 5);
}

