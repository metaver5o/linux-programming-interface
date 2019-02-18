# Threads: Introduction
- Threads are a mechanism for allowing concurrency
- The text doesn't say it, but I think a thread represents a single CPU core executing code
- Each process may contain multiple threads; by default there is one per process, minimum one
- `pthreads` is the POSIX standard for threading; there are numerous opaque data types associated
with pthreads, shown in table 29-1 (p. 620)
- Each thread has its own errno, otherwise they'd collide with each other
- threads are created with `pthread_create()`, which takes thread info and the function to execute by the thread as args
- threads can be terminated several ways - if the main thread terminates, if it gets cancelled, if the thread itself returns, etc
- Each thread has a unique `pthread_t` ID; note that because this must be opaque, we have functions like `pthread_equal()` to compare them
- `joining` refers to calling `pthread_join()` on another thread.
