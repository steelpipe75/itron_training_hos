#include "gmock/gmock.h"
#include "gtest/gtest.h"
extern "C" {
    #include <stdio.h>
    #include "tlsf.h"
}

static long long memblock[1024 * 4] = {0};
static long long memblock_pool[(1024 * 256 * 1) + (256)] = {0};

TEST(SampleTlsf, StructSize) {
    printf("tlsf_size()             = %d\n", tlsf_size());
    printf("tlsf_align_size()       = %d\n", tlsf_align_size());
    printf("tlsf_block_size_min()   = %d\n", tlsf_block_size_min());
    printf("tlsf_block_size_max()   = %d\n", tlsf_block_size_max());
    printf("tlsf_pool_overhead()    = %d\n", tlsf_pool_overhead());
    printf("tlsf_alloc_overhead()   = %d\n", tlsf_alloc_overhead());
}

TEST(SampleTlsf, CreateTest) {
    tlsf_t  tlsf_handle = NULL;
    pool_t  pool_handle = NULL;
    void*   ptr[128] = { 0 };
    size_t  size[128] = { 0 };
    int     i;

    for(i = 0; i < 128; i++) {
        ptr[i] = NULL;
        size[i] = 0;
    }

    printf("memblock        = %p\n", memblock);

    tlsf_handle = tlsf_create(memblock);
    printf("tlsf_handle     = %p\n", tlsf_handle);

    pool_handle = tlsf_add_pool(tlsf_handle, memblock_pool, 1024 * 256);
    printf("pool_handle     = %p\n", pool_handle);

    for(i = 0; i < 128; i++) {
        ptr[i] = tlsf_malloc(tlsf_handle, i);
        size[i] = tlsf_block_size(ptr[i]);
        printf("ptr[%3d] = %p, size[%3d] = %4d", i, ptr[i], i, size[i]);
        if((i+1)%2 == 0){
            printf("\n");
        }else{
            printf(", ");
        }
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    for(i = 0; i < 128; i++) {
        tlsf_free(tlsf_handle, ptr[i]);
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    for(i = 0; i < 128; i++) {
        ptr[i] = tlsf_memalign(tlsf_handle, 256, i);
        size[i] = tlsf_block_size(ptr[i]);
        printf("ptr[%3d] = %p, size[%3d] = %4d", i, ptr[i], i, size[i]);
        if((i+1)%2 == 0){
            printf("\n");
        }else{
            printf(", ");
        }
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    for(i = 0; i < 128; i++) {
        ptr[i] = tlsf_realloc(tlsf_handle, ptr[i], 256 + i);
        size[i] = tlsf_block_size(ptr[i]);
        printf("ptr[%3d] = %p, size[%3d] = %4d", i, ptr[i], i, size[i]);
        if((i+1)%2 == 0){
            printf("\n");
        }else{
            printf(", ");
        }
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    tlsf_walk_pool(pool_handle, NULL, NULL);

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    for(i = 0; i < 128; i++) {
        tlsf_free(tlsf_handle, ptr[i]);
    }

    tlsf_remove_pool(tlsf_handle, pool_handle);

    tlsf_destroy(tlsf_handle);
}

TEST(SampleTlsf, CreateWithPoolTest) {
    tlsf_t  tlsf_handle = NULL;
    pool_t  pool_handle = NULL;
    void*   ptr[128] = { 0 };
    size_t  size[128] = { 0 };
    int     i;

    for(i = 0; i < 128; i++) {
        ptr[i] = NULL;
        size[i] = 0;
    }

    printf("memblock        = %p\n", memblock_pool);

    tlsf_handle = tlsf_create_with_pool(memblock_pool, 1024 * 256);
    printf("tlsf_handle     = %p\n", tlsf_handle);

    pool_handle = tlsf_get_pool(tlsf_handle);
    printf("pool_handle     = %p\n", pool_handle);

    for(i = 0; i < 128; i++) {
        ptr[i] = tlsf_malloc(tlsf_handle, 256);
        size[i] = tlsf_block_size(ptr[i]);
        printf("ptr[%3d] = %p, size[%3d] = %4d", i, ptr[i], i, size[i]);
        if((i+1)%2 == 0){
            printf("\n");
        }else{
            printf(", ");
        }
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    for(i = 0; i < 128; i++) {
        tlsf_free(tlsf_handle, ptr[i]);
    }

    printf("tlsf_check      = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool = %d\n", tlsf_check_pool(pool_handle));

    tlsf_remove_pool(tlsf_handle, pool_handle);

    tlsf_destroy(tlsf_handle);
}


TEST(SampleTlsf, CreateTestPool2) {
    tlsf_t  tlsf_handle = NULL;
    pool_t  pool_handle_1 = NULL;
    pool_t  pool_handle_2 = NULL;
    void*   ptr[128] = { 0 };
    size_t  size[128] = { 0 };
    int     i;

    for(i = 0; i < 128; i++) {
        ptr[i] = NULL;
        size[i] = 0;
    }

    printf("memblock            = %p\n", memblock);

    tlsf_handle = tlsf_create(memblock);
    printf("tlsf_handle         = %p\n", tlsf_handle);

    pool_handle_1 = tlsf_add_pool(tlsf_handle, &(memblock_pool[0]), 1024 * 16);
    printf("pool_handle_1       = %p\n", pool_handle_1);

    pool_handle_2 = tlsf_add_pool(tlsf_handle, &(memblock_pool[1024 * 128]), 1024 * 16);
    printf("pool_handle_2       = %p\n", pool_handle_2);

    for(i = 0; i < 128; i++) {
        ptr[i] = tlsf_malloc(tlsf_handle, 256);
        size[i] = tlsf_block_size(ptr[i]);
        printf("ptr[%3d] = %p, size[%3d] = %4d", i, ptr[i], i, size[i]);
        if((i+1)%2 == 0){
            printf("\n");
        }else{
            printf(", ");
        }
    }

    printf("tlsf_check          = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool_1   = %d\n", tlsf_check_pool(pool_handle_1));
    printf("tlsf_check_pool_2   = %d\n", tlsf_check_pool(pool_handle_2));

    for(i = 0; i < 128; i++) {
        tlsf_free(tlsf_handle, ptr[i]);
    }

    printf("tlsf_check          = %d\n", tlsf_check(tlsf_handle));
    printf("tlsf_check_pool_1   = %d\n", tlsf_check_pool(pool_handle_1));
    printf("tlsf_check_pool_2   = %d\n", tlsf_check_pool(pool_handle_2));

    tlsf_remove_pool(tlsf_handle, pool_handle_1);
    tlsf_remove_pool(tlsf_handle, pool_handle_2);

    tlsf_destroy(tlsf_handle);
}

