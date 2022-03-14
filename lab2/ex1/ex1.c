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
    if(argc < 4){
        fprintf(stdout,"4 parameters expected, %d received\n", argc);
        return 0;
    }
    int number_of_students=0;
    int id, mark;
    long int register_number;
    char surname[MAX_CHARACTERS];
    char name[MAX_CHARACTERS];

    //  COUNT NUMBER OF STUDENTS FOR DYNAMIC ALLOCATION
    FILE *fp1 = fopen(argv[1],"r");
    if(!fp1){
        fprintf(stdout,"Cannot open the first file\n");
        return 0;
    }
    while(fscanf(fp1, "%d %ld %s %s %d\n", &id, &register_number, surname, name, &mark) != EOF)
        number_of_students++;
    fclose(fp1);
    student_t *students = (student_t *) malloc (number_of_students * sizeof(student_t));

    //  READ FROM FILE1
    fp1 = fopen(argv[1],"r");
    for(int i=0;i<number_of_students;i++)
        fscanf(fp1, "%d %ld %s %s %d\n", &students[i].id, &students[i].register_number, students[i].surname, students[i].name, &students[i].mark);
    fclose(fp1);

    //  STORE FILE1 INTO FILE 2
    int fd2 = open("file2",O_WRONLY, S_IWUSR);
    for(int i=0;i<number_of_students;i++){
        if(write(fd2, students+i, sizeof(student_t)) < 0){
            fprintf(stdout,"Error writing in file2\n");
            return 0;
        }
    }
    close(fd2);

    //  STORE FILE2 INTO FILE3
    student_t buffer;
    fd2 = open("file2",O_RDONLY, S_IRUSR);
    FILE *fp3 = fopen(argv[3],"w");
    for(int i=0;i<number_of_students;i++){
        read(fd2, &buffer, sizeof(student_t));
        fprintf(fp3, "%d %ld %s %s %d\n", buffer.id, buffer.register_number, buffer.surname, buffer.name, buffer.mark);
    }
    close(fd2);
    fclose(fp3);
    return 0;
}