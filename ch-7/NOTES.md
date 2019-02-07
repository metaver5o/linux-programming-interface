## Allocating memory on the heap
- What is the heap?
  - Variable size region of memory that can be used for at-runtime memory allocation
  - Heap size is limited via the `program break`, which can be adjusted via `sbrk()`
    - Notice that the `sbrk()` manpage dictates that it s a historical curiousity
    - `sbrk()` is no longer standardized
- `malloc()` and `free()`
  - `malloc()` allocates blocks of the heap and returns them to the user
  - `free()` releases them
  - `malloc()` can be controlled via `mallopt()`; `mallinfo()` can be used to retrieve information
- Other allocators
  - `realloc()` - reallocates memory
  - `calloc()` - zeroed out memory
  - `memalign()` / `posix_memalign()` - aligned memory
  - `alloca()` - stack memory; rare but useful in some sitauations where `malloc()`
    is slow or unable to be referenced again
- Should you free memory?
  - No - costs CPU time
  - Yes - makes bugs easier to find
  - Yes - will confuse Valgrind if you don't.
- Confused / want more practice?
  - Final exercise in `K&R` is to implement `malloc()`.
- Helpful tools:
  - `valgrind`, `dmalloc()` - useful tools
  - `mtrace()` / `muntrace()` - allow for tracing memory related function calls
  - `mcheck()` / `mprobe()` - allow inspection of allocated blocks

