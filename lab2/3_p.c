/*
Implement (simulate) the Linux shell command
cp  -R  <source>  <destination>
(with some extra feature) writing a C program with the following
specification

A C program is run with 2 strings on the command line:
dir_1  dir_2
where the two C strings indicate relative or absolute paths
of any two directory trees.
The program must copy the directory tree rooted in dir_1 into an isomorphic
directory tree dir_2.
For each file copied from the first to the second directory tree, the
program has to add two data fields on top of the destination file
specifying:
- the first one, the name of the file (the name only, not the path, as a
  C string)
- the second one, the size of the source (original) file
  (an integer value).
*/

#include "3.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

typedef struct stat stat_t;
typedef struct dirent dirent_t;

void visit(char *, char *);
void file_copy(char *, char *, char *);
void copy_file_content(char *, int, char *);

char *add_root(char *source_path, char *destination_path){
    char temp_source_path[PATH_SIZE];
    strcpy(temp_source_path, source_path);
    char *new_token = strtok(temp_source_path, "/");
    char *last_token = new_token;
    while(new_token != NULL){
        new_token = strtok(NULL, "/");
        if(new_token != NULL)
            last_token = new_token;
    }
    fprintf(stdout, "\nROOT FOUND: %s", source_path);
    return last_token;
}

void visit(char *source_path, char *destination_path){
    stat_t st;
    DIR *d_opendir = opendir(source_path);
    dirent_t *d_dirent;
    while((d_dirent = readdir(d_opendir)) != NULL){
        if(strcmp(d_dirent->d_name, ".") && strcmp(d_dirent->d_name, "..")){
            char new_source_path[PATH_SIZE];
            char new_destination_path[PATH_SIZE];
            sprintf(new_source_path, "%s/%s", source_path, d_dirent->d_name);
            sprintf(new_destination_path, "%s/%s", destination_path, d_dirent->d_name);
            stat(new_source_path, &st);
            if(S_ISDIR(st.st_mode)){
                fprintf(stdout, "\nDIRECTORY FOUND: %s", new_source_path);
                directory_copy(new_source_path, new_destination_path, false);
            }else{
                fprintf(stdout, "\nFILE FOUND: %s", new_source_path);
                file_copy(new_source_path, new_destination_path, d_dirent->d_name);
            }
        }
    }
}

void directory_copy(char *source_path, char *destination_path, bool root_flag){
    if(root_flag)
        sprintf(destination_path, "%s/%s", destination_path, add_root(source_path, destination_path));
    mkdir(destination_path, S_IRUSR | S_IWUSR | S_IXUSR);
    fprintf(stdout, "\nDIRECTORY GENERATED: %s\n", destination_path);
    visit(source_path, destination_path);
}

void file_copy(char *source_path, char *destination_path, char *filename){
  int file_id = open(destination_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
  fprintf(stdout, "\nFILE GENERATED: %s", destination_path);
  copy_file_content(source_path, file_id, filename);
  fprintf(stdout, "\nFILE COPIED: %s\n", destination_path);
  close(file_id);
}

void copy_file_content(char *original_file_path, int new_file_id, char *filename){
    FILE *original = fopen(original_file_path, "r");
    char c;
    write(new_file_id, filename, strlen(filename));
    write(new_file_id, "\n", 1);
    int size = 0;
    while(fscanf(original, "%c", &c) != EOF)
        size++;
    char size_string[FILE_SIZE_SIZE];
    sprintf(size_string, "%d bytes", size);
    write(new_file_id, size_string, strlen(size_string));
    write(new_file_id, "\n\n", 2);
    fclose(original);
    original = fopen(original_file_path, "r");
    while(fscanf(original, "%c", &c) != EOF)
        write(new_file_id, &c, 1);
}
