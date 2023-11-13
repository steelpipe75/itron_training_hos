#ifndef MOCK_MY_RAND_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Mock_my_rand {
public:
    MOCK_METHOD0(my_rand, int(void));
};
extern void SetdMock_my_rand(Mock_my_rand *p);

#endif /* #ifndef MOCK_MY_RAND_HPP*/

