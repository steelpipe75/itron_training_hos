#include "mock_my_rand.hpp"

extern "C" {
#include "my_rand.h"
}

static Mock_my_rand* pMock = NULL;

void SetdMock_my_rand(Mock_my_rand* p) {
    pMock = p;
}


extern "C" int my_rand(void){
    int ret = 0;
    if(pMock != NULL) {
        ret = pMock->my_rand();
    }else{
        ADD_FAILURE();
    }
    return ret;
}


