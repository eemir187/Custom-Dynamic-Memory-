#include <pthread.h>
#include "memory.h"
#include <new>
#include "string.h"

#include <cstring>
#include <cstdlib>

#include <climits>
#include <stdint.h>


char* chunk_ptr = NULL;
char* chunk_end = NULL;
const size_t CHUNK_SIZE = 8 * 1024;


MemoryBlock* head = NULL;
MemoryBlock* tail = NULL;
size_t total_used = 0;



MemoryBlock* findMemoryBlock(size_t size) {
  MemoryBlock* curr = head;

  while (curr != NULL) {
    if (curr->isFree && curr->size >= size) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}


MemoryBlock* allocate_memory(size_t size) {
  
  size_t total = sizeof(MemoryBlock) + size;
  
  
  
  if (chunk_ptr == nullptr || chunk_ptr + total > chunk_end) {
    
    size_t grab;

    if (total > CHUNK_SIZE) {
      grab = total;
    }
    else {
      grab = CHUNK_SIZE;
    }
    
    void* new_slab = snp::sbrk(grab);
    if (new_slab == (void*)-1) {
      return NULL;
    }

    chunk_ptr = (char*)new_slab;
    chunk_end = chunk_ptr + grab;
  }

  // chop of block from chunk
  MemoryBlock* block = (MemoryBlock*)chunk_ptr;
  chunk_ptr += total; 

  
  block->size = size;
  block->isFree = false;
  block->memoryPointer = block + 1;
  block->next = NULL;


  
  if (!head) {
    head = tail = block;
  } else {
    tail->next = block;
    tail = block;
  }

  return block;
}



void shrinkBreak(MemoryBlock* block) {
  
  while (block == tail && block->isFree) {
    if (snp::brk(block) != 0) {
      return;   
    } 

    chunk_ptr = NULL;
    chunk_end = NULL;

    if (block == head) {
      head = tail = NULL;
      return;
    }

   
    MemoryBlock* prev = head;
    while (prev->next != block) {
      prev = prev->next;
    }

    prev->next = NULL;
    tail = block = prev;                
  }
  
}




namespace snp
{


void *Memory::malloc(size_t size)
{

  if (size == 0 || size > PTRDIFF_MAX) {
    return NULL;
  }

  MemoryBlock* block = findMemoryBlock(size);
  if (!block) {
    block = allocate_memory(size);
    if (!block) {
      return NULL;
    }
  }
  else {
    block->isFree = false;
  }

  
  total_used += block->size;
  return block->memoryPointer;


}


void Memory::free(void *ptr)
{
    
  if (!ptr) {
    return;
  }

  MemoryBlock* curr = head;
  while (curr && curr->memoryPointer != ptr) {
    curr = curr->next;
  }
  // invalid pointer 
  if (!curr) {
    exit(-1);
  }
  // double free error
  if (curr->isFree) {
    exit(-1);
  }

  curr->isFree = true;
  total_used -= curr->size;

  for (MemoryBlock* p = head; p && p->next; ) {
    if (p->isFree && p->next->isFree) {
      MemoryBlock* next_block = p->next;
            
        
      p->size += next_block->size;
      p->next = next_block->next;
            
      if (tail == next_block) {
        tail = p; 
      }
    } 
    else {
      p = p->next;
    }
  }

  shrinkBreak(tail);
}




void *Memory::calloc(size_t num_memb, size_t size_each)
{
  
  if(num_memb == 0 || size_each == 0) {
    return NULL;
  }

  size_t total = num_memb * size_each;
  
  void* memory = malloc(total);
  if (memory != NULL) {
    std::memset(memory, 0, total);
  }
  else {
    return NULL;
  }

  return memory;
}

size_t Memory::total_used_memory() noexcept
{
  return total_used;
}

size_t Memory::free_block_info(int type) noexcept
{
  MemoryBlock* curr = head;
  while (curr != NULL) {
    if (curr->isFree) {
        if (type != 0) {
          return curr->size;
        }
        else {
          return (size_t)curr->memoryPointer;
        }                          
    }
    curr = curr->next;
  }


  return 0;
}





}

