#include "class_public.h"

void honk_vehicle(void){
  fprintf(stdout, "tuut tuut!\n");
}

void honk_car(car_t c){
    c.superclass.honk();
}

void initialize_vehicle(vehicle_t *v, char *i_brand, void (*i_honk)(void)){
    strcpy(v->brand, i_brand);
    v->honk = i_honk;
}

void initialize_car(car_t *c, char *i_brand, char *i_model, void (*i_honk)(void), void (*i_honk2)(car_t)){
    c->superclass.init = initialize_vehicle;
    c->superclass.init(&c->superclass, i_brand, i_honk);
    c->honk = i_honk2; 
    strcpy(c->modelName, i_model);
}