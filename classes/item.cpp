#include "item.hpp"

Item::Item(){
  name = "NULL";
  type = Weapon;
  stat = 0;
}

Item::Item(std::string n, Type t, int s){
  name = n;
  type = t;
  stat = s;
}

Item::~Item(){}

int Item::get_stat(){
  return stat;
}

Type Item::get_type(){
  return type;
}

std::string Item::get_name(){
  return name;
}

//need to fix this
std::ostream& operator<<(std::ostream& lhs, const Item& rhs){
  Item o = rhs;
  std::string t;
  switch(o.get_type()){
    case Weapon:
      t = "Weapon";
      break;
    case Armor:
      t = "Armor";
      break;
    case Potion:
      t = "Potion";
      break;
    case Money:
      t = "Money";
      break;
  }

  std::cout << o.get_name() << "\t" << t << "\t" << o.get_stat();
  return lhs;
}
