#include "class/player.hpp"
#include "class/enemy.hpp"
#include "class/dungeon.hpp"
#include <vector>

#pragma once

class Game{
private:
  bool play;
  Player P;
  std::vector<Location> map;
  std::vector<Dungeon> dungeons;
public:
  Game();
  ~Game();
  void initialize();
  void play();
  void save();
  void load(bool reload);
  void quit();
  Enemy generate_enemy();
};
