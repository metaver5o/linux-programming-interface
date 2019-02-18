## File descriptors
- Small nonnegative integer the operating system uses to refer to an open file
- 3 primary ones given to each process - 0 (stdin), 1 (stdout), 2 (stderr)
- I/O functions can be called on all file-types viz. `universality of I/O`; there is no special "socket open" or "tty open"
- `open()` can be used to open a file for reading or writing and returns a file descriptor
- `creat()` can create and open a file; `creat()` is equivalent to `open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);`
