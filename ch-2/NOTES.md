## The kernel
* What is a process?
  * "The kernel can load a new program into memory, providing it with the resources (e.g., CPU, memory, and access to files) that it needs in order to run. Such an instance of a running program is termed a process"
* What is the kernel?
  * Core component of the operating system that manages access to hardware on behalf of other software
* Major OS tasks:
  - Process scheduling and management enabling preemption and multitasking
  - Memory management allowing for virtualization
  - Filesystem
  - Other device management
  - Networking
* Two modes of execution, kernel and user
  - Linux API provides gateway to switch between them
* Kernel essentially acts as an intermediary between processes and hardware
## The shell
* What is a shell?
  * "A shell is a special-purpose program designed to read commands typed by a user and execute appropriate programs in response to those commands."
  * Many variants, `bash` being most common.
* Key tools `man`, `bash`, `-h`
  * Most syscalls are available via the manpages; many CLI tools are just wrapped around certain API functions
## Users and groups
* What is a user?
  - Abstraction defined by unique username and id; has a shell, group id, and home dir
  - Special superuser `root`
* What is a group?
  - Organization of users
* Key tools: `whoami`, `id`
## Single Directory Hierarchy, Directories, Links, and Files
* What is a file?
  - "Discrete organization of data on some storage medium"
* What is a directory?
  - "A directory is a special file whose contents take the form of a table of filenames coupled with references to the corresponding files."
* What is a link?
  - "This filename-plus-reference association is called a link"
* What is a symbolic link?
  - "a symbolic link provides an alternative name for a file. But whereas a normal link is a filename-plus-pointer entry in a directory list, a symbolic link is a specially marked file containing the name of another file"
* What is the difference between absolute and relative pathnames?
  - "An absolute pathname begins with a slash (/) and specifies the location of a file with respect to the root directory... a relative pathname specifies the location of a file relative to a process’s current working directory (see below), and is distinguished from an absolute pathname by the absence of an initial slash."
* How do file permissions work?
  - Each file has a user owner and a group owner
  - Each file has 9 total permissions bits: read/write/execute for user, group, and world
  - Also applies to directories with slightly different rules
* Key tools: `ls`, `tree`, `stat`, `file`, `chmod`
## File I/O model
- Universality of I/O - same file related system calls used on all files
- "UNIX systems have no end-of-file character; the end of a file is detected by a read that returns no data."
* What is a file descriptor?
  - an integer I/O system calls use to identify an opened file
* Question for thought: what does opening a file actually do?
  - https://stackoverflow.com/questions/33495283/what-does-opening-a-file-actually-do
## Programs and Processes
* What is a program?
  - human readable code vs machine code
  - `filter` is a special type of program reading from stdin and writing to stdout. `grep`, `wc`, `cat`
* What is a process address space?
  - On most modern systems, each process's view of memory is that it is the only process being executed, so it has
    access to the entire address space. The kernel facilitates translation between virtual addresses and hardware addresses.
  - A process organizes its address space into segments:
      * Text: the instructions of the program.
      * Data: the static variables used by the program.
      * Heap: an area from which programs can dynamically allocate extra memory.
      * Stack: a piece of memory that grows and shrinks as functions are called and return and that is used to allocate storage for local variables and function call linkage information.
- Processes can be started with `fork()` or `execve()`
- Fork bombs! - https://en.wikipedia.org/wiki/Fork_bomb
- Processes have a unique id; each process's parent id is also associated with it
  - additionally a process has a real user id / group id to identify which user/group it belongs to
  - also effective and supplemental user/group id, which allows for changing permissions / acting as another user/group
  - privileged processes have an id of `0`, which are either created by other privileged processes or have their id changed
  - Processes have capabilities: http://man7.org/linux/man-pages/man7/capabilities.7.html
- Init process is the first process with PID 1, runs as superuser, spawns other processess, and can't be killed
- Daemons are long living and run in the background
- Processes have environment list where env variables are stored; this is copied on fork
- Processes can have limited access to resources via setlimit()
  - hard vs softlimit
* Key tools `ps`, `top`, `htop`,
## Memory mappings
* File mappings vs anonymous mappings
* Shared memory can be used for IPC if non-anonymous
## Static and shared libs
- static linking vs dynamic linking
## IPC / synchronization
- Linux offers different ways to allow processes to communicate:
  - signals, which are used to indicate that an event has occurred;
  - pipes (familiar to shell users as the | operator) and FIFOs, which can be used to
  transfer data between processes;
  - sockets, which can be used to transfer data from one process to another, either on the same host computer or on different hosts connected by a network;
  - file locking, which allows a process to lock regions of a file in order to prevent other processes from reading or updating the file contents;
  - message queues, which are used to exchange messages (packets of data) between processes;
  - semaphores, which are used to synchronize the actions of processes; and
  - shared memory, which allows two or more processes to share a piece of memory. When one process changes the contents of the shared memory, all of the other processes can immediately see the changes.
## Signals
* Signals are their own class of IPC and function as software interrupts
* The kernel brokers signals between processes, and can send them for a variety of reasons
* Many programs implement signal handlers
* Key tools: `kill`, `signal(3)`
## Threads
* What is a thread?
  * Individual sequence of execution within a process; each process can have several.
## Job control
* Major shells allow for processes to be executed in groups as process groups or `jobs` and provide features
  for controlling them
## Sessions, Controlling Terminals, and Controlling Processes
* `session`s are collections of process groups, which are created by the `session leader`
* `sessions` have a `controlling terminal`, which is the first opened terminal device by the process.
* The process opening the controlling terminal becomes the `controlling process`
* Every session has at least one foreground process, which is halted if the terminal closes
## Pseudoterminal
* Master-slave program pair; driver program performs actions a user would at the terminal
* Slave device provides a terminal-like interface for master program to drive it with
## Date and time
* Real time - calendar / unix time
* CPU time - amount of time spent executing the process in either usermode time or kernel mode time
* Key tools: `time`
## Client-server architecture, Realtime
- Nothing new here
## `/proc` filesystem
- Linux provides a file-like interface to kernel data structures, which are frequently human-readable
