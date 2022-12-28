#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vehicle_s vehicle_t;
typedef struct car_s car_t;

struct vehicle_s {
  char brand[10];
  void (*honk)(void);
  void (*init)(vehicle_t *v, char *b, void (*f)(void));
};

struct car_s{
  char modelName[10];
  vehicle_t superclass;
  void (*honk)(car_t);
  void (*init)(car_t *c, char *b, char *m, void (*f)(void), void (*f2)(car_t));
};