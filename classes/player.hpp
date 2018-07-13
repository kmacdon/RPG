#include "character.hpp"
#include "location.hpp"
#include "enemy.hpp"

#pragma once

class Player: public Character{
  int experience;
  int level;
  int next_level;
  std::vector<Item> inventory;
  std::vector<int> quantity;
  Location* current;

  //methods

public:
  Player();
  Player(std::string n, int h, int mh, int s[4], Item w, Item a, int next_level);
  ~Player();
  void move();
  Location* get_location();
  void set_location(Location *L);
  void use_item(Item *a);
  void print_stats();
  void print_inventory();
  void add_exp(int e);
  void add_item(Item d);
  Item* get_item(std::string);
  void remove_item(std::string s);
  void battle(Enemy &E);
  friend nlohmann::json compress(Player P);
};
