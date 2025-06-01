#include <new>
#include <cstdio>
#include <cstdlib>

#ifdef assert
#undef assert
#endif
#define assert(val) do {\
 if ((val) == 0) exit(-1);\
} while (0);

int main()
{
    try {
        std::size_t size = 512UL * 1024UL * 1024UL * 1024UL;
        size_t* p = new size_t[size];
        (void)p;
    }
    catch (const std::bad_alloc &e) {
        printf("exception caught!\n");
    }

    return 0;
}
