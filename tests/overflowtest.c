// overflow_simple.c
#include <stdlib.h>
#include <stdio.h>
#include "memory.h"

int main(void) {
    // 1) allocate 16 bytes
    char *p = (char*)malloc(16);
    if (!p) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    // 2) write one byte too many
    p[20] = 'X';

    // 3) freeing should detect the stomped canary and exit(-1)
    free(p);


    // if we get here, the overflow was NOT caught
    fprintf(stderr, "ERROR: overflow went undetected!\n");
    return 1;
}
