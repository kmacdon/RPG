#include "dungeon.hpp"
#include "player.hpp"

void Dungeon::explore(WINDOW * win, Player &P){
  waddstr(win, description.c_str());
  Enemy E(enemy);
  P.battle(E, win);
  if(!P.is_alive())
    return;
  P.add_item(win, loot);
  std::string s = "While exploring " + name + ", you found a " + loot.get_name();
  waddstr(win, s.c_str());
  wrefresh(win);
}
