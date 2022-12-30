#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "2.h"

#define bool int
#define true 1
#define false 0

typedef struct student_s student_t;

struct student_s{
  int id;
  long register_;
  char surname[MAX_LENGTH];
  char name[MAX_LENGTH];
  int mark;
};

void read_student(int, int);
void write_student(int, int);
student_t *generate_student(int, long, char *, char *, int);

void menu(char *file){
  int f = open(file, O_RDWR);
  bool flag = true;
  char command;
  int id;
  while(flag){
    fprintf(stdout, "\n\n-> ");
    fscanf(stdin, "\n%c", &command);
    switch (command) {
      case 'R':
        fscanf(stdin, " %d", &id);
        read_student(f, id);
        break;
      case 'W':
        fscanf(stdin, " %d", &id);
        write_student(f, id);
        break;
      default:
        flag = false;
        fprintf(stdout, "terminating...\n");
        break;
    }
  }
  return;
}

void read_student(int f, int id){
  student_t *s = (student_t *) malloc(sizeof(student_t));
  lseek(f, (id - 1) * sizeof(student_t), SEEK_SET);
  read(f, s, sizeof(student_t));
  fprintf(stdout, "%d %ld %s %s %d", s->id, s->register_, s->surname, s->name, s->mark);
}

void write_student(int f, int id){
  lseek(f, (id - 1) * sizeof(student_t), SEEK_SET);
  int id_, mark;
  long register_;
  char name[MAX_LENGTH];
  char surname[MAX_LENGTH];
  fprintf(stdout, "Data: ");
  fscanf(stdin, "%d %ld %s %s %d", &id_, &register_, surname, name, &mark);
  student_t *s = generate_student(id_, register_, surname, name, mark);
  write(f, s, sizeof(student_t));
}

student_t *generate_student(int id, long register_, char *surname, char *name, int mark){
  student_t *s = (student_t *) malloc(sizeof(student_t));
  s->id = id;
  s->register_ = register_;
  strcpy(s->surname, surname);
  strcpy(s->name, name);
  s->mark = mark;
  return s;
}
