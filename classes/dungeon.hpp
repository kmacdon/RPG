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
  void explore(WINDOW * win, Player &P);
  friend void to_json(nlohmann::json& j, const Dungeon& D);
  friend void from_json(const nlohmann::json& j, Dungeon& D);
};
