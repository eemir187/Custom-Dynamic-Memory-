#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>      
#include "memory.h"
 
#ifdef assert
#undef assert
#endif
#define assert(val) do {\
 if ((val) == 0) exit(-1);\
} while (0);
 
int main(void)
{
    // first brk
    void* brk0 = sbrk(0);
    printf("%p\n", brk0);

    
    void* x = malloc(24);
    void* y = malloc(40);
    assert(x && y);

    void* new_brk = sbrk(0);
    assert( new_brk > brk0 );     
    printf("%p\n", new_brk);

    // after freeing first block new break must be the same becuase we didnt shrink
    free(x);
    assert( sbrk(0) == new_brk );
    printf("%p\n", sbrk(0));

    // new brk after free
    free(y);
    void* brk_after_free = sbrk(0);
    assert( brk_after_free < new_brk );
    printf("%p\n", brk_after_free);

    

    return 0;
}
 