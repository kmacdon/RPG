#include <string>
#include <iostream>
#include "json_conversion.hpp"

#pragma once

class Item{
  std::string name;
  std::string type;
  int stat;

public:
  Item();
  Item(std::string n, std::string t, int s);
  ~Item();
  int get_stat();
  std::string get_type();
  std::string get_name();
  friend void to_json(nlohmann::json& j, const Item& I);
  friend void from_json(const nlohmann::json& j, Item& I);
};

std::ostream& operator<<(std::ostream& lhs, const Item& rhs);
