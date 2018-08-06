#include "dungeon.hpp"
#include "player.hpp"
#include "../data/constants.hpp"
#include "../helper/error.hpp"
#include <fstream>

void Dungeon::explore(WINDOW * win, WINDOW * stats, Player &P){
  print_log(MAIN_LOG, "Entering explore() ");
  waddstr(win, description.c_str());
  P.battle(load_enemy(enemy), win, stats);
  if(!P.is_alive())
    return;
  P.add_item(win, loot);
  std::string s = "While exploring " + name + ", you found a " + loot.get_name();
  waddstr(win, s.c_str());
  wrefresh(win);
  print_log(MAIN_LOG, "Exiting explore() ");
}

Enemy Dungeon::load_enemy(std::string e){
  print_log(MAIN_LOG, "Loading enemy " + e);
  std::ifstream input(ENEMY_FILE);
  nlohmann::json j;
  while(input >> j){
    if(j["object"] == "END"){
      break;
    }
    print_log(MAIN_LOG, j["name"]);
    if(j["name"] == e){
      print_log(MAIN_LOG, "Loaded enemy " + e);
      Enemy E = j;
      return E;
    }
  }
  std::string s = j["name"];
  print_log(MAIN_LOG, "Error: Failed to load enemy " + s);
  Enemy E;
  return E;
}
