#include "dungeon.hpp"
#include "player.hpp"
#include "../data/constants.hpp"
#include "../error.hpp"

void Dungeon::explore(WINDOW * win, WINDOW * stats, Player &P){
  print_log(MAIN_LOG, "Entering explore() ");
  waddstr(win, description.c_str());
  Enemy E(enemy);
  P.battle(E, win, stats);
  if(!P.is_alive())
    return;
  P.add_item(win, loot);
  std::string s = "While exploring " + name + ", you found a " + loot.get_name();
  waddstr(win, s.c_str());
  wrefresh(win);
  print_log(MAIN_LOG, "Exiting explore() ");
}