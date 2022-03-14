#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_CHARACTERS 31

struct student_s{
    int id;
    long int register_number;
    char surname[MAX_CHARACTERS];
    char name[MAX_CHARACTERS];
    int mark;
};
typedef struct student_s student_t;

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stdout,"2 parameters expected, %d received\n", argc);
        return 0;
    }
    char command, junk;
    int target;
    student_t student;
    int fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    do{
        fscanf(stdin,"%c", &command);
        if(command == 'E')
            break;
        fscanf(stdin,"%d%c", &target, &junk);
        lseek(fd, (target - 1) * sizeof(student_t), SEEK_SET);
        switch(command){
            case 'R':
                read(fd, &student, sizeof(student_t));
                fprintf(stdout,"%d %ld %s %s %d\n", student.id, student.register_number, student.surname, student.name, student.mark);
                break;
            case 'W':
                fprintf(stdout,"Data: ");
                fscanf(stdin, "%d %ld %s %s %d%c",  &student.id, &student.register_number, student.surname, student.name, &student.mark, &junk);
                write(fd, &student, sizeof(student_t));
                break;
            default:
                break;
        }
    }while(command == 'R' || command == 'W');
    close(fd);
    return 0;
}