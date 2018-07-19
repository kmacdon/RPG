#include "player.hpp"
#include "enemy.hpp"
#include "location.hpp"
#include <nlohmann/json.hpp>

#pragma once

class Game{
private:
  friend class Screen;
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
  bool reload;

  //Methods
  void create_map();

public:
  //Constructors
  Game();
  ~Game() {};

  //Methods
  void initialize();
  void load_data(std::string s);
  void welcome_screen(WINDOW * win);
  void inventory_screen(WINDOW * win);
  void main_screen();
  void map_screen(WINDOW * win);
  void play();
  void start();
  void save(WINDOW * win);
  Player get_player() {return P;};
  //void quit();
  int status(bool print = false);

  //Members

};
