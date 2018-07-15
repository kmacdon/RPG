#include "character.hpp"
#include "item.hpp"

#pragma once

class Enemy: public Character{
  //Members
  Item loot;
  float loot_rate;
  std::string description;


public:
  //Constructors
  Enemy();
  Enemy(std::string n);
  Enemy(std::string n, int s[4]);
  Enemy(std::string n, int h, int mh, int s[4], int e, Item W, Item a, Item l, float lr, std::string d);
  ~Enemy() {};

  //Methods
  Item get_loot();
  int drop_exp() {return experience;};
  std::string get_description() {return description;};
  bool drop_loot();
};
