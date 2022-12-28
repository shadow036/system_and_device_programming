#include "class_public.h"

int main(){
  vehicle_t v;
  v.init = initialize_vehicle;
  v.init(&v, "ford", honk_vehicle);
  v.honk();

  car_t c;
  c.init = initialize_car;
  c.init(&c, "panda", "s300", honk_vehicle, honk_car);
  c.honk(c);
}