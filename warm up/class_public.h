#include "class_private.h"

void honk_vehicle(void);
void honk_car(car_t);
void initialize_vehicle(vehicle_t *, char *, void (*)(void));
void initialize_car(car_t *, char *, char *, void (*)(void), void (*)(car_t));
