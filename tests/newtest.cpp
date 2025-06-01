#include <stddef.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>


#ifdef assert
#undef assert
#endif
#define assert(val) do {\
 if ((val) == 0) exit(-1);\
} while (0);

int main()
{
    int* a = new int(7);

    printf("%d", *a);

    assert(a && *a == 7);
    delete a;

    int b = 10;
    int* array = new int[b];

    for (int i = 0; i < b; i++) {
      array[i] = i;
    } 

    for (int i = 0; i < b; i++) {
      assert(array[i] == i);
    } 

    delete[] array;

    return 0;
}
