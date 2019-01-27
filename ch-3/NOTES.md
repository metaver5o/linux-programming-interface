## What is a system call?
* "A system call is a controlled entry point into the kernel, allowing a process to request that the kernel perform some action on the process’s behalf."
* http://man7.org/linux/man-pages/man2/syscalls.2.html
* Section 2 of the library is for syscalls - 3 is for library functions.
  - compare `fopen` with `open`
*  A system call changes the processor state from user mode to kernel mode, so that the CPU can access protected kernel memory.
*  The set of system calls is fixed. Each system call is identified by a unique number. (This numbering scheme is not normally visible to programs, which identify system calls by name.)
* What happens when you call a syscall?
  1. syscall wrapper function is executed
  2. wrapper copies arguments to specific registers to prepare for trap function
  3. wrapper function copies syscall number to eax
  4. trap is executed (later replaced by `sysenter`)
  5. kernel invokes `system_call()` handler routine, which:
    a. saves register values to kernel stack
    b. checks validity of syscall number
    c. invokes system call service routine indexed in `sys_call_table`
    d. cleans up and returns
  6. Returns value and errno is set
* Review errno and return conventions
* As such, invoking syscalls has a lot of overhead.
## Library functions
* Many library functions do not need to use syscalls - the entire execution just goes through
the C stdlib code in the process address space and returns to the caller (as opposed to execution
going into the OS)
* different versions of the c std lib exist
## Handling errors
* Use of `perror` and `errno`
## Portability
- Use feature test macros for system discovery / defining constants
- Also use platform independent data types like `size_t` with size guaranetees
