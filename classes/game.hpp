#include "player.hpp"
#include "enemy.hpp"
#include "location.hpp"
#include <nlohmann/json.hpp>
#include "dungeon.hpp"

#pragma once

class Game{
private:
  friend class Screen;

  //Members
  Player P;
  std::vector<Location> map;
  //std::vector<Dungeon> dungeons;
  bool play_game;
  bool reload;

  //Methods
  void create_map();
  Dungeon generate_dungeon(std::string s);
  Enemy load_enemy(std::string e);
public:
  //Constructors
  Game();
  ~Game() {};

  //Methods
  void initialize();
  void load_data(std::string s);
  void welcome_screen(WINDOW * win);
  void main_screen();
  void map_screen(WINDOW * win);
  void poi_screen(WINDOW * win);
  void play();
  void start();
  void save(WINDOW * win);
  Player get_player() {return P;};
  //void quit();
  int status(bool print = false);

  //Members

};
