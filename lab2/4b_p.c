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
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct dirent dirent_t;
typedef struct stat stat_t;

void visit(char *, FILE *);

struct thread_s{
    char *root;
};

void *thread(void *parameter){
    char *root = ((thread_t *) parameter)->root;
    char filename[FILENAME_MAX];
    sprintf(filename, "%d-%lu", getpid(), pthread_self());
    FILE *file_pointer = fopen(filename, "w");
    visit(root, file_pointer);
    fclose(file_pointer);
    pthread_exit(0);
}

thread_t *generate_thread(char *root){
    thread_t *t = (thread_t *) malloc(sizeof(thread_t));
    t->root= (char *) malloc(sizeof(char) * strlen(root));
    strcpy(t->root, root);
    return t;
}

void visit(char *current_directory, FILE *file_pointer){
//    fprintf(stdout, "\n%ld: %s\n", pthread_self(), current_directory);
    fprintf(file_pointer, "%lud %s\n", pthread_self(), current_directory);
    stat_t st;
    stat(current_directory, &st);
    if(S_ISDIR(st.st_mode)){
        DIR *d = opendir(current_directory);
        dirent_t *drnt;
        while((drnt = readdir(d)) != NULL){
            if(strcmp(drnt->d_name, ".") && strcmp(drnt->d_name, "..")){
                char new_directory[1000];
                sprintf(new_directory, "%s/%s", current_directory, drnt->d_name);
                visit(new_directory, file_pointer);
            }
        }
        closedir(d);
    }
}
