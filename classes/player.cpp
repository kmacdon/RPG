#include "player.hpp"
#include "../helper/functions.hpp"
#include "../helper/error.hpp"
#include <fstream>
#include "../data/constants.hpp"
#include "../helper/screen.hpp"
//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Player::Player(){
  name = "NULL";
}

Player::Player(std::string n, int h, int mh, std::unordered_map<std::string, int> s, Item w, Item a, int next_level){
  name = n;
  health = h;
  max_health = mh;
  skills = s;
  weapon = w;
  armor = a;
  alive = true;
  level = 1;
  experience = 0;
  next_level = 100;
}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

void Player::move(WINDOW * win, WINDOW * stats, std::string s){
  current->change_location(win, stats, this, s);

}

Location* Player::get_location(){
  return current;
}

void Player::set_location(Location* L){
  current = L;
}

void Player::print_stats(WINDOW * win){
  wmove(win, 0, 0);
  std::string s = "| Name: " + name + "\n";
  waddstr(win, s.c_str());
  s = "| Level: " + std::to_string(level) + "\n";
  waddstr(win, s.c_str());
  s = "| Health: " + std::to_string(health) + "/" + std::to_string(max_health) + "\n";
  waddstr(win, s.c_str());
  s = "| Experience: " + std::to_string(experience) + "\n| Next Level:" + std::to_string(next_level) + "\n";
  waddstr(win, s.c_str());
  s = "| Str: " + std::to_string(skills["STR"]) + "  End: " + std::to_string(skills["END"]) + "\n| Spd: " + std::to_string(skills["SPD"]);
  waddstr(win, s.c_str());
  s = "  Lck: " + std::to_string(skills["LCK"]) + "\n";
  waddstr(win, s.c_str());
  waddstr(win, "|__________________");
}

void Player::add_exp(WINDOW * win, int e, int &y){
    experience += e;
    std::string s = "You gained " + std::to_string(e) + " experience!\n";
    waddstr(win, s.c_str());
    y += 2;
    if(experience >= next_level){
      level_up(win,y);
    }
    s = std::to_string(next_level - experience) + " experience until the next level.\n";
    waddstr(win, s.c_str());
    ++y;
    max_health = 10 + 5*(level - 1);
    health = max_health;
}

void Player::level_up(WINDOW * win, int &y){
  experience -= next_level;
  next_level = 100 * ++level;
  std::string s = "You leveled up! Now at level " + std::to_string(level) + "\n";
  waddstr(win, s.c_str());
  ++y;
  waddstr(win, "Select a skill to upgrade:\n");
  ++y;
  std::vector<std::string> choices;
  choices.push_back("STR");choices.push_back("END");choices.push_back("SPD");choices.push_back("LCK");
  std::string choice = select(win, choices, y, false);
  s = choice + " increased by 1\n";
  waddstr(win, s.c_str());
  ++y;
  skills[choice]++;
}

//Print out inventory
void Player::print_inventory(WINDOW * win, WINDOW * stats){
  print_log(MAIN_LOG, "Opening inventory screen");

  char a = 'a';
  cbreak();
  noecho();

  //Display inventory screen and get selections
  while(1){
    //refresh stats screen
    print_stats(stats);
    wrefresh(stats);

    int y = 0;
    wclear(win);
    wrefresh(win);
    int ch;
    wmove(win, 0, 0);
    if(inventory.size() == 0){
      waddstr(win, "Your inventory is empty. Press \'q\' to exit.");
      wrefresh(win);
      while(1){
        ch = wgetch(win);
        if(ch == 'q')
          break;
      }
      break;
    }

    //create vector of possible choices
    std::vector<std::string> v;
    for(int i = 0; i < inventory.size(); i++){
      std::string s = inventory[i].get_name() + " " + std::to_string(inventory[i].get_stat());
      v.push_back(s);
    }
    //selection screen
    std::string choice = select(win, v, y, true);
    print_log(MAIN_LOG, "Choice = " + choice);
    if(choice == "q")
      break;
    v = split(choice, ' ');
    for(int j = 1; j < v.size() - 1; j++){
      v[0] += " " + v[j];
    }
    //match choice to inventory
    for(int i = 0; i < inventory.size(); i++){
      if(v[0] == inventory[i].get_name()){
        print_log(MAIN_LOG, "Choice matched");
        wmove(win, 0, 20); // used for printing message
        use_item(win, &inventory[i]);
        wrefresh(win);
        ch = wgetch(win); // just so player can read message
      }
    }
  }
  echo();
  nocbreak();
}

Item* Player::get_item(WINDOW * win, std::string s){
  print_log(MAIN_LOG, "Entering get_item()");
  for(int i = 0; i < inventory.size(); i++){
    std::string n = inventory[i].get_name();
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    if(n == s){
      print_log(MAIN_LOG, "Exiting get_item()");
      return &inventory[i];
    }
  }
  waddstr(win, "Sorry. That item is not in your inventory");
  print_log(MAIN_LOG, "Exiting get_item() without finding item");
  return nullptr;
}

void Player::use_item(WINDOW * win, Item *a){
  print_log(MAIN_LOG, "Entering use_item()");
  //empty pointer
  if(!a){
    return;
  }
  int s = a->get_stat();
  Item I;
  std::string name = a->get_name();
  print_log(MAIN_LOG, "Using item = " + name);
  std::string msg;
  //match item type
  switch(a->get_type()){
    case Potion:
      if(health == max_health){
        waddstr(win, "Already at max health");
        wrefresh(win);
        break;
      }
      msg = "Using " + name;
      waddstr(win, msg.c_str());
      wrefresh(win);
      health = (health + s > max_health) ? max_health : health + s;
      remove_item(a->get_name());
      break;
    case Weapon:
      msg = "Equipping " + name;
      waddstr(win, msg.c_str());
      wrefresh(win);
      I = weapon;
      weapon = *a;
      *a = I;
      break;
    case Armor:
      I = armor;
      armor = *a;
      *a = I;
      break;
    default:
      break;
  }
  wrefresh(win);
  print_log(MAIN_LOG, "Exiting use_item()");
}

void Player::add_item(WINDOW * win, Item d){
  print_log(MAIN_LOG, "Entering add_item()");
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() == d.get_name()){
      quantity[i]++;
      return;
    }
  }
  inventory.push_back(d);
  quantity.push_back(1);
  print_log(MAIN_LOG, "Exiting add_item()");
}

void Player::remove_item(std::string s){
  print_log(MAIN_LOG, "Entering remove_item()");
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() ==  s){
      quantity[i]--;
      if(quantity[i] == 0){
        inventory.erase(inventory.begin() + i);
        quantity.erase(quantity.begin() + i);
      }
      break;
    }
  }
  print_log(MAIN_LOG, "Exiting remove_item()");
}

void Player::battle(Enemy E, WINDOW * win, WINDOW * stats){
  print_log(MAIN_LOG, "Entering battle()");
  wclear(win);
  std::string s;
  s = "You are attacked by " + E.get_description() + "\n";
  waddstr(win, s.c_str());
  unsigned char ch;
  int x = 0;
  int y = 0;
  wmove(win, ++y, x);
  std::vector<std::string> v;
  v.push_back("Attack");
  v.push_back("Use Item");
  print_log(MAIN_LOG, "Entering battle loop");
  while(is_alive() && E.is_alive()){
    std::string choice = select(win, v, y, false);
    //selection made
    y++;
    if(choice == "Attack"){
      y += 5;
      std::string m = std::to_string(y);
      print_log(BATTLE_LOG, m.c_str());
      print_log(BATTLE_LOG, "Selected Attack");
      if(get_speed() >= E.get_speed()){
        defend(win, E.attack(win));
        E.defend(win, attack(win));
      }
      else {
        E.defend(win, attack(win));
        defend(win, E.attack(win));
      }
    }
    else if(choice == "Use Item"){
      wclear(win);
      wrefresh(win);
      print_inventory(win, stats);
      wclear(win);
      wrefresh(win);
      defend(win, E.attack(win));
      y += 2;
    }
  }
  char pause = wgetch(win);
  print_log(MAIN_LOG, "Exiting battle loop");
  //Player is dead
  if(!is_alive())
    return;

  add_exp(win, E.drop_exp(), y);

  if(E.drop_loot())
    add_item(win, E.get_loot());
  wrefresh(win);
  pause = wgetch(win);
  print_log(MAIN_LOG, "Exiting battle()");
  wclear(win);
  wrefresh(win);
}
