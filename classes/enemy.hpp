#include "character.hpp"
#include "item.hpp"
#include "json_conversion.hpp"

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
  Enemy(std::string n, std::unordered_map <std::string, int> s);
  Enemy(std::string n, int h, int mh, std::unordered_map <std::string, int> s, int e, Item W, Item a, Item l, float lr, std::string d);
  ~Enemy() {};

  //Methods
  Item get_loot();
  int drop_exp() {return experience;};
  std::string get_description() {return description;};
  bool drop_loot();
  friend void to_json(nlohmann::json& j, const Enemy& E);
  friend void from_json(const nlohmann::json& j, Enemy& E);
};
