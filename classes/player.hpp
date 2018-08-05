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
  Player(std::string n, int h, int mh, std::unordered_map<std::string, int> s, Item w, Item a, int next_level);
  ~Player() {};

  //Methods
  void move();
  Location* get_location();
  void set_location(Location *L);

  void print_stats(WINDOW * win);
  void add_exp(WINDOW * win, int e, int &y);
  void level_up(WINDOW * win, int &y);
  //Item Functionss
  void add_item(WINDOW * win, Item d);
  void use_item(WINDOW * win, Item *a);
  Item* get_item(WINDOW * win, std::string);
  void remove_item(std::string s);
  void battle(Enemy &E, WINDOW * win, WINDOW * stats);
  void print_inventory(WINDOW * win, WINDOW * stats);

  //Setters
  void set_name(std::string n) {name = n;};

  //Friend
  friend void to_json(nlohmann::json& j, const Player& P);
  friend void from_json(const nlohmann::json& j, Player& P);
};
