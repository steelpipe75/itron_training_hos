#include <stdio.h>
#include "tlsf.h"


static long long memblock_1[1024 * 1024 * 1] = {0};
static long long memblock_2[1024 * 1024 * 1] = {0};


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    tlsf_t tlsf_handle_1 = NULL;
    tlsf_t tlsf_handle_2 = NULL;

    printf("tlsf sample\n");

    tlsf_handle_1 = tlsf_create(memblock_1);
    tlsf_handle_2 = tlsf_create_with_pool(memblock_2, 1024*128);


    tlsf_destroy(tlsf_handle_1);
    tlsf_destroy(tlsf_handle_2);

    return 0;
}
