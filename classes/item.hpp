#include <string>
#include <iostream>

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
};

std::ostream& operator<<(std::ostream& lhs, const Item& rhs);
