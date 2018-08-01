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

public:
  void explore(WINDOW * win, WINDOW * stats, Player &P, Enemy E);
  std::string get_name(){return name;};
  std::string get_enemy(){return enemy;};
  friend void to_json(nlohmann::json& j, const Dungeon& D);
  friend void from_json(const nlohmann::json& j, Dungeon& D);
};
