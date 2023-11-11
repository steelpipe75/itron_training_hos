#include "gtest/gtest.h"

extern "C" int get_eat_count(int num);
extern void wait_for_hos(void);

TEST(SampleTest, EatCount) {
    wait_for_hos();
    EXPECT_EQ(get_eat_count(2), 5);
}

