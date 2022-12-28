#include "page_28_public.h"

void *read_(void *file){
  FILE *f = (FILE *) file;
  char next_character;
  int return_value = fscanf(f, "%c", &next_character);
  if(return_value == EOF){
    flag = 1;
    pthread_exit(0);
  }
  read_registers[offsets[READ][READ]] = next_character;
  offsets[READ][READ] = (offsets[READ][READ] + 1) % 3;
  pthread_exit(0);
}

void *transform(void *idk){
  if(read_registers[offsets[TRANSFORM][READ]] >= 97 && read_registers[offsets[TRANSFORM][READ]] <= 122)
    transform_registers[offsets[TRANSFORM][TRANSFORM]] = read_registers[offsets[TRANSFORM][READ]] - 32;
  else
    transform_registers[offsets[TRANSFORM][TRANSFORM]] = read_registers[offsets[TRANSFORM][READ]];
  offsets[TRANSFORM][TRANSFORM] = (offsets[TRANSFORM][TRANSFORM] + 1) % 2;
  offsets[TRANSFORM][READ] = (offsets[TRANSFORM][READ] + 1) % 3;
  pthread_exit(0);
}

void *display(void *idk){
  char target = transform_registers[offsets[DISPLAY][TRANSFORM]];
  fprintf(stdout, "%c", target);
  offsets[DISPLAY][TRANSFORM] = (offsets[DISPLAY][TRANSFORM] + 1) % 2;
  pthread_exit(0);
}

void setup(){
  offsets[READ][READ] = 0;
  offsets[TRANSFORM][READ] = 0;
  offsets[TRANSFORM][TRANSFORM] = 0;
  offsets[DISPLAY][TRANSFORM] = 0;
}

void display_registers(){
  int i = 0;
  fprintf(stdout, "\n\nread registers");
  for(i = 0; i < 3; i++)
    fprintf(stdout, "\n%d: %c", i, read_registers[i]);
  fprintf(stdout, "\ntransform registers");
  for(i = 0; i < 2; i++)
    fprintf(stdout, "\n%d: %c", i, transform_registers[i]);
}

void display_offsets(){
  int i, j = 0;
  fprintf(stdout, "\noffsets");
  char x[10];
  char y[10];
  for(i = 0; i < 3; i++){
    for(j = 0; j < 2; j++){
      if(filter_offsets(i, j, x, y))
        fprintf(stdout, "\n(%s, %s): %d", x, y, offsets[i][j]);
    }
  }
  fprintf(stdout, "\n\n");
}

bool filter_offsets(int i, int j, char *x, char *y){
  bool valid_flag = True;
  if(i == 0 && j == 0){
    strcpy(x, "read");
    strcpy(y, "read");
  } else if(i == 1 && j == 0){
    strcpy(x, "transform");
    strcpy(y, "read");
  } else if(i == 1 && j == 1){
    strcpy(x, "transform");
    strcpy(y, "transform");
  } else if(i == 2 && j == 1){
    strcpy(x, "display");
    strcpy(y, "transform");
  } else
    valid_flag = False;
  return valid_flag;
}

int main(int argc, char *argv){
  /*if(argc != 2){
    fprintf(stdout, "\nwrong number of parameters!");
    return -1;
  }*/
  int counter = 0;
  FILE *f = fopen("input", "r");
  char next_character = ' ';
  pthread_t tids[3];
  void *ret_val;
  while(counter < END){
    if(counter < END_READ)
      pthread_create(&tids[READ], NULL, read_, (void *) f);
    if(counter >= START_TRANSFORM && counter < END_TRANSFORM)
      pthread_create(&tids[TRANSFORM], NULL, transform, NULL);
    if(counter >= START_DISPLAY)
      pthread_create(&tids[DISPLAY], NULL, display, NULL);
    if(counter < END_READ)
      pthread_join(tids[READ], &ret_val);
    if(counter >= START_TRANSFORM && counter < END_TRANSFORM)
      pthread_join(tids[TRANSFORM], &ret_val);
    if(counter >= START_DISPLAY)
      pthread_join(tids[DISPLAY], &ret_val);
    if(counter < START_DISPLAY)
      counter++;
    else
      counter += flag;
    /*display_registers();
    display_offsets();
    fprintf(stdout, "\nflag: %d\ncounter: %d\n", flag, counter);*/
  }
  return 0;
}
