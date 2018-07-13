#include "character.hpp"
#include "item.hpp"

#pragma once

class Enemy: public Character{
  Item loot;
  float loot_rate;
  std::string description;
  //methods

public:
  Enemy();
  Enemy(std::string n);
  Enemy(std::string n, int s[4]);
  Enemy(std::string n, int h, int mh, int s[4], int e, Item W, Item a, Item l, float lr, std::string d);
  ~Enemy();
  Item get_loot();
  int drop_exp();
  std::string get_description();
  bool drop_loot();
};
