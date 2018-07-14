#include "player.hpp"
#include "enemy.hpp"
#include "location.hpp"
#include <nlohmann/json.hpp>

#pragma once

class Game{
private:
  Player P;
  std::vector<Location> map;
  //std::vector<Dungeon> dungeons;
  void create_map();
public:
  bool play_game;
  Game();
  ~Game();
  void initialize(bool reload);
  //void welcome_screen();
  void play();
  void save();
  void load_data(std::string s);
  int status(bool print = false);
  //void quit();
  void get_map();
};
