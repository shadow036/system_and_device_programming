/*
A C program receives N parameters on the command line.
Each parameter indicates a relative or an absolute path to
a directory tree.
The program has to run N threads (one for each argument).
Each one of these threads recursively visits one of the directories,
and, for each directory entry, it displays its thread identifier
and the directory entry name.
The main thread waits for the termination of all threads.
When all threads have visited their directory also the program
ends.

Version A
As all output lines are generated independently by each single
thread, printing messages from different threads are interleaved
on standard output.

Version B
To avoid the problem of Version A, Version B uses files.
In other words, each thread stores its output on a file whose name
is generated (to avoid conflicts) based on the process and the
thread identifiers.
When all working threads end, the main thread copies all files on
standard output with the desired strategy (and no interruption).

Version C for Future development
Once synchronization primitives have been introduced
----------------------------------------------------
Generalize version B by using a centralized thread (the "output thread")
dedicated to generating the entire application output.
All threads resort to the centralized and dedicated output thread to
perform all operations on standard output.
The output thread is executed within a critical section, and
- it just awaits for more output to come in
- when the input arrives, it displays it.
Notice that by "centralizing" the output the application can optimize it.
For example, the application may decide to store messages on files (like
the program for Version B), it may use a dedicated data structure to
store messages and sort them somehow, it may decide which verbosity level
to use, it may compute output statistics, etc.
*/

#include "4.h"

int main(int argc, char **argv){
    void *return_value;
    pthread_t *thread_ids = (pthread_t *) malloc(argc * sizeof(pthread_t));
    for(int i = 1; i < argc; i++){
        thread_t *t = generate_thread(argv[i]);
        pthread_create(thread_ids + i, NULL, thread, (void *) t);
    }
    for(int i = 1; i < argc; i++)
        pthread_join(thread_ids[i], (void **) &return_value);
    return 0;
}
