#include <string>
#include <iostream>
#include "json_conversion.hpp"

#pragma once
enum Type {Weapon, Armor, Potion, Money};

class Item{
  std::string name;
  Type type;
  int stat;

public:
  Item();
  Item(std::string n, Type t, int s);
  ~Item();
  int get_stat();
  Type get_type();
  std::string get_name();
  friend void to_json(nlohmann::json& j, const Item& I);
  friend void from_json(const nlohmann::json& j, Item& I);
};

std::ostream& operator<<(std::ostream& lhs, const Item& rhs);
