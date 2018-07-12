#include "character.hpp"
#include "location.hpp"
#include "enemy.hpp"
#include <vector>

#pragma once

class Player: public Character{
  int experience;
  int level;
  int next_level;
  std::vector<Item> inventory;
  int quantity[50];
  Location* current;
  //Location *current;

  //methods
  Item get_item(std::string);
public:
  Player();
  Player(std::string n, int h, int mh, int s[4], Item w, Item a);
  ~Player();
  void move();
  void set_location(Location *L);
  void use_item(Item *a);
  void print_stats();
  void print_inventory();
  void add_exp(int e);
  void add_item(Item d);
  void remove_item(std::string s);
  void battle(Enemy E);
};
