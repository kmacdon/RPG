#include <string>
#include <iostream>
#include "json_conversion.hpp"

#pragma once
enum Type {Weapon, Armor, Potion, Money};

class Item{
private:
  //Members
  std::string name;
  Type type;
  int stat;

public:
  //Constructors
  Item();
  Item(std::string n, Type t, int s);
  ~Item() {};

  //Members
  //Getters
  int get_stat() {return stat;};
  Type get_type() {return type;};
  std::string get_name() {return name;};

  //Friend
  friend void to_json(nlohmann::json& j, const Item& I);
  friend void from_json(const nlohmann::json& j, Item& I);
};

std::ostream& operator<<(std::ostream& lhs, const Item& rhs);
