#include <new> 
#include <stdlib.h> 
#include "memory.h"

namespace snp
{




void *Memory::_new(size_t size) 
{ 

  void* new_memory = snp::Memory::malloc(size);
  if (!new_memory) {
    throw std::bad_alloc();
  } 


  return new_memory;
} 

void Memory::_delete(void * p) 
{ 

  if(p) {
    snp::Memory::free(p);
  }
  else {
    // null pointer
    exit(-1);
  }



} 





}

