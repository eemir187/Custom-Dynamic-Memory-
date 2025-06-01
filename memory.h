#ifndef SNP_MEMORY_H_
#define SNP_MEMORY_H_

#include "unistd.h"
#include "stdlib.h"

typedef struct MemoryBlock {
  size_t size;
  bool isFree;
  void* memoryPointer;
  struct MemoryBlock* next;
} MemoryBlock;

namespace snp {
  class Memory
  {
  public:
    static void *calloc(size_t num_memb, size_t size_each);
    static void *malloc(size_t size);
    static void free(void *ptr);

    static void *_new(size_t size);
    static void _delete(void *ptr);

    static size_t total_used_memory() noexcept;
    static size_t free_block_info(int type) noexcept;


  };

  void* sbrk(intptr_t __delta);
  int brk(void* __addr);
}




void *malloc(size_t size) noexcept;
void *calloc(size_t num_memb, size_t size_each) noexcept;
void free(void *ptr) noexcept;
void* operator new(size_t size);
void operator delete(void *address ) noexcept;
void* operator new[] ( size_t size );
void operator delete[] ( void* address ) noexcept;

#endif /* SNP_MEMORY_H_ */

