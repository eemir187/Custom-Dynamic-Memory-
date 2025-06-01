#include <stdio.h>
#include <stdlib.h>
#include "memory.h"       

#ifdef assert
#undef assert
#endif
#define assert(val) do {\
 if ((val) == 0) exit(-1);\
} while (0);

/* util‑function prototypes (C linkage, provided by util.cpp) */
extern size_t total_used_memory(void);
extern size_t free_block_info(int);

int main(void)
{
    /* fresh allocator state */
    assert( total_used_memory() == 0 );
    assert( free_block_info(1) == 0 );
    assert( free_block_info(0) == 0 );

    /* allocate two blocks */
    void *a = malloc(16);
    void *b = malloc(32);

    assert(a && b);
    assert( total_used_memory() == 48 );
    assert( free_block_info(1) == 0 );          /* no free yet */

    /* free first block – becomes first free */
    size_t a_addr = (size_t)a;                  /* save value */
    free(a);

    assert( total_used_memory() == 32 );
    assert( free_block_info(1) == 16 );         /* size */
    assert( free_block_info(0) == a_addr );     /* start address */

    /* free second block – total goes to zero */
    free(b);
    assert( total_used_memory() == 0 );

    
    return 0;
}
