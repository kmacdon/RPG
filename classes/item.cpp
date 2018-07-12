#include "item.hpp"

Item::Item(){
  name = "";
  type = "";
  stat = 0;
}

Item::Item(std::string n, std::string t, int s){
  name = n;
  type = t;
  stat = s;
}

Item::~Item(){}

int Item::get_stat(){
  return stat;
}

std::string Item::get_type(){
  return type;
}

std::string Item::get_name(){
  return name;
}

//need to fix this
std::ostream& operator<<(std::ostream& lhs, const Item& rhs){
  Item o = rhs;
  std::cout << o.get_name() << "\t" << o.get_type() << "\t" << o.get_stat();
  return lhs;
}
