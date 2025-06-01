# Custom Dynamic Memory Management (malloc, calloc, free, new, delete)

This project is a personal implementation of dynamic memory management in C++, including custom versions of `malloc`, `calloc`, `free`, and support for `new` and `delete`.

## Features

- ✅ Custom `malloc` and `calloc`
  - Allocates memory from a manually managed memory chunk.
  - Reuses freed blocks to reduce fragmentation.
  - `calloc` zero-initializes allocated memory.

- ✅ Custom `free` with block coalescing
  - Frees allocated memory.
  - Merges adjacent free blocks automatically.
  - Detects and exits on double free or invalid pointer.

- ✅ Dynamic memory shrinking
  - Releases memory back to the OS using `brk` when the last blocks are free.

- ✅ Custom `new` and `delete`
  - Full support for C++ `new`, `delete`, `new[]`, and `delete[]`.
  - Throws `std::bad_alloc` on failure.

- ✅ Memory usage reporting
  - `total_used_memory()` returns total memory in use.
  - `free_block_info(int type)` returns size or address of the first free block (for testing/debugging).

- ✅ Test automation
  - A shell script `run_tests.sh` is included to automatically run all test binaries in the `build/` folder.
  - Handles expected failure cases, timeouts, and proper output coloring.

## Files Overview

| File           | Description                                         | 
|----------------|-----------------------------------------------------|
| `malloc.cpp`   | Implements `malloc`, `calloc`, and `free` logic     |
| `new.cpp`      | Implements C++ `new`, `delete`, `new[]`, `delete[]` |
| `memory.h`     | Declares `MemoryBlock` and memory API functions     |
| `util.cpp`     | Wraps system calls (`sbrk`, `brk`) and provides C interfaces |
| `tests`        | Folder where test source files are placed and compiled from   |
