#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "1.h"

typedef struct person_s person_t;

static person_t *generate_person(int, long, char *, char *, int);

struct person_s{
  int id;
  long register_;
  char surname[MAX_LENGTH];
  char name[MAX_LENGTH];
  int mark;
};

static person_t *generate_person(int id, long register_, char *surname,
  char *name, int mark){
  person_t *p = (person_t *) malloc(sizeof(person_t));
  p->id = id;
  p->register_ = register_;
  strcpy(p->name, name);
  strcpy(p->surname, surname);
  p->mark = mark;
  return p;
}

void **open_files(char *file1, char *file2, char *file3){
  FILE *f1 = fopen(file1, "r");
  int f2 = open(file2, O_RDWR);
  FILE *f3 = fopen(file3, "w");
  void **files = (void **) malloc(3 * sizeof(void *));
  /*files[0] = (void *) malloc(sizeof(void));
  files[1] = (void *) malloc(sizeof(void));
  files[2] = (void *) malloc(sizeof(void));*/
  files[0] = (void *) f1;
  files[1] = (void *) &f2;
  files[2] = (void *) f3;
  return files;
}

void text_to_binary(FILE *text, int binary){
  int id, mark;
  long register_;
  char name[MAX_LENGTH];
  char surname[MAX_LENGTH];
  while(fscanf(text, "%d %ld %s %s %d", &id, &register_, surname, name, &mark) != EOF){
    person_t *p = generate_person(id, register_, surname, name, mark);
    write(binary, (void *) p, sizeof(person_t));
  }
}

void binary_to_text(int binary, FILE *text){
  lseek(binary, 0, SEEK_SET);
  person_t *p = (person_t *) malloc(sizeof(person_t));
  while(read(binary, p, sizeof(person_t)) > 0)
    fprintf(text, "%d %ld %s %s %d\n", p->id, p->register_, p->surname, p->name, p->mark);
}

void close_files(void **files){
  fclose((FILE *) files[0]);
  close(*((int *) files[1]));
  fclose((FILE *) files[2]);
  free(files);
}
