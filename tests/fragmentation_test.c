/* dbg_free_info.c – dump free_block_info after each free() */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "memory.h"

// we declare the util functions here so the compiler knows about them
extern size_t total_used_memory();
extern size_t free_block_info(int type);

int main(void) {
    // allocate three blocks so we can see what happens in various orders
    void *p1 = malloc(16);
    void *p2 = malloc(32);
    void *p3 = malloc(64);
    printf("Allocated:\n");
    printf("  p1 = %p (16)\n", p1);
    printf("  p2 = %p (32)\n", p2);
    printf("  p3 = %p (64)\n\n", p3);

    // free the first block
    free(p1);
    uintptr_t a1 = free_block_info(0);
    size_t    s1 = free_block_info(1);
    printf("After free(p1):\n");
    printf("  first free addr = %p\n", (void*)a1);
    printf("  first free size = %zu\n\n", s1);

    // free the second block
    free(p2);
    uintptr_t a2 = free_block_info(0);
    size_t    s2 = free_block_info(1);
    printf("After free(p2):\n");
    printf("  first free addr = %p\n", (void*)a2);
    printf("  first free size = %zu\n\n", s2);

    // free the third block
    free(p3);
    uintptr_t a3 = free_block_info(0);
    size_t    s3 = free_block_info(1);
    printf("After free(p3):\n");
    printf("  first free addr = %p\n", (void*)a3);
    printf("  first free size = %zu\n\n", s3);

    return 0;
}
