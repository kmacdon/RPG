#include "item.h"

Item::Item(){

}

Item::Item(char n[], char t[], int s){
  assign(name, n, sizeof(n)/sizeof(*n));
  assign(type, t, sizeof(t)/sizeof(*t);
  stat = s;
}

Item::~Item(){
  
}
