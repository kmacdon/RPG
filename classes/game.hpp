#include "player.hpp"
#include "enemy.hpp"
#include "location.hpp"
#include <nlohmann/json.hpp>

#pragma once

class Game{
private:
  //Parameters
  const int NAME_LENGTH;
  const std::string SAVE_FILE;
  const std::string LOG_FILE;
  const std::string DEFAULT_FILE;
  const std::string MAP_FILE;

  //Game Objects
  Player P;
  std::vector<Location> map;
  //std::vector<Dungeon> dungeons;
  void create_map();
public:
  bool play_game;
  Game();
  ~Game();
  void initialize(bool reload);
  void play();
  void save();
  void load_data(std::string s);
  int status(bool print = false);
  //void quit();
  void get_map();
};
