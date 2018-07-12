#include "functions.hpp"
#include <iostream>
void assign(int a[], int b[], int size){
  for(int i = 0; i < size; i++){
    a[i] = b[i];
  }
}

void assign(std::vector <Location *> &a, std::vector <Location *> b){
  for(int i = 0; i < a.size(); i++){
     a[i] = b[i];
  }
}
