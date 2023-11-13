#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "mock_my_rand.hpp"
extern "C" {
#include "my_rand.h"
}

extern "C" int get_eat_count(int num);
extern "C" void wait_eating(void);

TEST(SampleTest, EatCount) {
    Mock_my_rand mock;
    using ::testing::Return;
    EXPECT_CALL(mock, my_rand()).WillRepeatedly(Return(1));
    SetdMock_my_rand(&mock);
    wait_eating();
    EXPECT_EQ(get_eat_count(2), 5);
}

