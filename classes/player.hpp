#include "character.hpp"
#include "location.hpp"
#include "enemy.hpp"
#include "json_conversion.hpp"

#pragma once

class Player: public Character{
  friend class Game;
  friend class Screen;
  //members
  int experience;
  int level;
  int next_level;
  std::vector<Item> inventory;
  std::vector<int> quantity;
  Location* current;

public:
  //Constructors
  Player();
  Player(std::string n, int h, int mh, int s[4], Item w, Item a, int next_level);
  ~Player() {};

  //Methods
  void move();
  Location* get_location();
  void set_location(Location *L);

  void print_stats();
  void print_inventory();
  void add_exp(int e);
  //Item Functionss
  void add_item(Item d);
  void use_item(Item *a);
  Item* get_item(std::string);
  void remove_item(std::string s);
  void battle(Enemy &E);

  //Setters
  void set_name(std::string n) {name = n;};

  //Friend
  friend void to_json(nlohmann::json& j, const Player& P);
  friend void from_json(const nlohmann::json& j, Player& P);
};
