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

  //Members
  Player P;
  std::vector<Location> map;
  //std::vector<Dungeon> dungeons;
  bool play_game;

  //Methods
  void create_map();

public:
  //Constructors
  Game();
  ~Game() {};

  //Methods
  void initialize(bool reload);
  void load_data(std::string s);
  void play();
  void save();
  //void quit();
  int status(bool print = false);

  //Members

};
