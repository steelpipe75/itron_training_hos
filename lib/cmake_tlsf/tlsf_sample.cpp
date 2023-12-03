#include "gmock/gmock.h"
#include "gtest/gtest.h"
extern "C" {
    #include <stdio.h>
    #include "tlsf.h"
}

static long long memblock[1024 * 1024 * 1] = {0};

TEST(SampleTlsf, CreateTest) {
    tlsf_t tlsf_handle = NULL;
    pool_t pool_handle = NULL;

    tlsf_handle = tlsf_create(memblock);
    pool_handle = tlsf_get_pool(tlsf_handle);

    printf("memblock    = %p\n", memblock);
    printf("tlsf_handle = %p\n", tlsf_handle);
    printf("pool_handle = %p\n", pool_handle);

    tlsf_destroy(tlsf_handle);
}

TEST(SampleTlsf, CreateWithPoolTest) {
    tlsf_t tlsf_handle = NULL;
    pool_t pool_handle = NULL;

    tlsf_handle = tlsf_create_with_pool(memblock, 1024 * 256);
    pool_handle = tlsf_get_pool(tlsf_handle);

    printf("memblock    = %p\n", memblock);
    printf("tlsf_handle = %p\n", tlsf_handle);
    printf("pool_handle = %p\n", pool_handle);

    tlsf_destroy(tlsf_handle);
}



