#include <stdlib.h>
#include <stdio.h>

int main(void) {
    // allocate 100 KB in 1024-byte chunks
    const int  CHUNK = 1024;
    const int  N     = 100 * 1024 / CHUNK;  // = 100
    void* ptrs[N];

    for (int i = 0; i < N; i++) {
        ptrs[i] = malloc(CHUNK);
        if (!ptrs[i]) {
            fprintf(stderr, "malloc failed at i=%d\n", i);
            return 1;
        }
    }
    // touch the pages so sbrk actually commits them
    for (int i = 0; i < N; i++) {
        ((char*)ptrs[i])[0] = 42;
    }
    printf("Allocated %d×%d B = %d KB\n", N, CHUNK, N*CHUNK/1024);
    return 0;
}
