#include "player.hpp"
#include "enemy.hpp"
#include "location.hpp"

#pragma once

class Game{
private:
  bool play;
  Player P;
  std::vector<Location> map;
  //std::vector<Dungeon> dungeons;
  void create_map();
  //these following functions are used when loading data
  Location create_Location(std::string s);
  Player create_Player(std::string s);
public:
  Game();
  ~Game();
  void initialize(bool reload);
  //void play();
  //void save();
  void load_data(std::string s);
  int status(bool print = false);
  //void quit();
  void get_map();
};
