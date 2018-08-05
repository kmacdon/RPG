#include <ncurses.h>
#include <string>
#include "json_conversion.hpp"
#include "item.hpp"

#pragma once

class Player;

class Dungeon{
private:
  std::string name;
  std::string enemy;
  Item loot;
  std::string description;
  Enemy load_enemy(std::string e);

public:
  void explore(WINDOW * win, WINDOW * stats, Player &P);
  std::string get_name(){return name;};
  friend void to_json(nlohmann::json& j, const Dungeon& D);
  friend void from_json(const nlohmann::json& j, Dungeon& D);
};
