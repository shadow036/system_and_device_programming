#include <fcntl.h>
#include <stdio.h>

int main99(){
    int n1 = 3;
    int n2 = 4;
    printf(sizeof(float));
    float a1[3];
    a1[0] = 1.5;
    a1[1] = 4.5;
    a1[2] = 5.5;
    float a2[4];
    a2[0] = 2.3;
    a2[1] = 3.3;
    a2[2] = 6.3;
    a2[3] = 7.9;
    int f1 = open("input4.1", O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    int f2 = open("input4.2", O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    write(f1, (void *) &n1, sizeof(int));
    write(f2, (void *) &n2, sizeof(int));
    for(int i = 0; i < 3; i++)
        write(f1, (void *) a1 + i, sizeof(float));
    for(int i = 0; i < 4; i++)
        write(f2, (void *) a2 + i, sizeof(float));
    close(f1);
    close(f2);
}
