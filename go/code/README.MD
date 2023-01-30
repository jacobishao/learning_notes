# a example to simulate golang pprof's work.

it use setitimer system call to send a SIGPROF signal to thread, invoking the signal handler.
the code doesn't contain any stacktrace part.
