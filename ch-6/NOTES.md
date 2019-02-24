# Processes
- A `process` is an instance of an executing program.
- A `program` is a file containing a range of information that describes how to con- struct a process at run time.
- Each process has a PID, a unique integer identifying it
  - Init is 1
  - All must be less than 32,767

- Memory layout of a process is divided into `segments` (sometimes called `sections` to avoid confusion
with unrelated concept of x86 "segments"):
  - `text` - contains program code
  - `initialized data` - contains global / static variables with explicit initialization
  - `uninitialized data` - same as above but excluding uninitialized ones
  - `stack` - storage for "automatic" variables
  - `heap` - storage for dynamic memory; top of the heap is the `program break`
  - Some of these can be inferred in C from external variables (etext, edata, and end)
- An `application binary interface (ABI)` is a set of rules specifying how a binary executable should exchange information with some service (e.g., the kernel or a library) at run time. Among other things, an ABI specifies which registers and stack locations are used to exchange this information, and what meaning is attached to the exchanged values.

- `virtual memory management` allows a program to exploit `locality of reference`. Namely:
  - `spacial locality` is a tendency of programs to referece addresses near recently addressed ones
  - `temporal locality` is the tendency to access the same address in the near future
  - The nice thing about this is that you can fully execute a program while keeping only a portion of its address space in memory.
- Memory virtualization splits memory used by each program into small fixed size units called `pages`.
- RAM can thus be divided into `page frames`
- Pages that need to be present in memory are called the `resident set`; non-resident pages
  can be sent to `swap space` on disk
- If an accessed page is not in memory, a `page fault` occurs and the process holds until it is
fetched from disk
- For each process, the kernel maintains a `page table` dictating what virtual pages map to what
physical pages for each page in a process's virtual address space.
  - Not every address in the VAD needs to have a page associated with it, since much of it is unused
  - Accessing an address with no entry in the page table raises a SIGSEGV signal

- The stack pointer keeps track of the logical top of the stack, but note that its relation
in terms of address to higher or lower values is an implementation detail.

- Discussion of argc and argv

- Discussion of environment (key value pairs set in process address space)

- Nonlocal jumps can be used to implement error handling

## API calls
  - `getpid()` - gets a process's pid
  - `getppid()` - get's a parent's pid
  - `getopt()` can be used to parse command line args
  - `getenv()` and `putenv()` both use "key=val" syntax
  - `setenv()` and `unsetenv()` use key and val arguments
  - `clearenv()` erases the environment


## Utilities
  - `size` - displays sizes of segments in binary file
