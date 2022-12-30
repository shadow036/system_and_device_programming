/*
An ASCII file has lines with the following format:
- An identifier, i.e., an integer value varying from 1 to the number
  of rows in the file (e.g., 1, 2, etc.)
- A register number, i.e., a long integer of 6 digits (e.g., 164678)
- A surname, i.e., a string of a maximum of 30 characters (e.g., Rossi)
- A name, i.e., a string of a maximum of 30 characters (e.g., Mario)
- An examination mark, i.e., an integer value.

The following is a correct example of such a file:

1 100000 Romano Antonio 25
2 150000 Fabrizi Aldo 22
3 200000 Verdi Giacomo 15
4 250000 Rossi Luigi 30

Write a C program in UNIX which is run with 3 file names on the
command line:
file_1  file_2  file_3
and which can:
- Read the *text* file file_1 (with the previous format) and
  store the same information into file file_2 in *binary* format.
  The binary format file must have *fixed-length* records (i.e.,
  each record must include an integer + a long integer + 31 characters
  + 31 characters + an integer).
- Read back the *binary* file file_2 and store it as a *text*
  into file file_3 (with the same format of file_1).

Suggestions
-----------
Manipulate text files using C library functions and binary files
using the I/O UNIX library.
As an alternative, use only the UNIX library *but* operate on the ASCII
file on a byte-by-byte basis (and then move forward and backward to
the record-by-record representation).

Verify that files file_input_1 and file_output_2 are indeed equivalent
using the shell command "wc" and "diff".
*/
#include "1.h"

int main(int argc, char **argv){
  if(argc != 4){
    fprintf(stderr, "wrong number of parameters");
    return -1;
  }
  void **files = open_files(argv[1], argv[2], argv[3]);
  text_to_binary((FILE *) (files[0]), *((int *) (files[1])));
  binary_to_text(*((int *) (files[1])), (FILE *) (files[2]));
  close_files(files);
}
