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

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0

#define PATH_SIZE 1000
#define FILE_SIZE_SIZE 100000

void directory_copy(char *, char *, bool);
