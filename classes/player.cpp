#include "player.hpp"
#include "../functions.hpp"
//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Player::Player(){
  name = "NULL";
}

Player::Player(std::string n, int h, int mh, int s[4], Item w, Item a, int next_level){
  name = n;
  health = h;
  max_health = mh;
  assign(skills, s, 4);
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

void Player::move(){
  std::cout << "Where would you like to go to next?\n";
  current->print_connections();
  std::string s;
  std::getline(std::cin, s);
  std::vector<std::string> c = current->list_connections();
  for(int i = 0; i < c.size(); i++){
    if(c[i] == s){
      current = current->get_connection(s);
      return;
    }
  }
  std::cout << "That is not a valid location." << std::endl;
}

Location* Player::get_location(){
  return current;
}

void Player::set_location(Location* L){
  current = L;
}

void Player::print_stats(WINDOW * win){
  //Character::print_stats();
  wmove(win, 0, 0);
  std::string s = "| Experience: " + std::to_string(experience) + "\n| Next Level:" + std::to_string(next_level) + "\n";
  waddstr(win, s.c_str());
  s = "| Str: " + std::to_string(skills[0]) + "  End: " + std::to_string(skills[1]) + "\n| Spd: " + std::to_string(skills[2]);
  waddstr(win, s.c_str());
  s = "  Lck: " + std::to_string(skills[3]) + "\n";
  waddstr(win, s.c_str());
  waddstr(win, "|__________________");
}

void Player::print_inventory(){
  for(int i = 0; i < inventory.size(); i++){
    std::cout << inventory[i] << "\tx" << quantity[i] << std::endl;
  }
}

void Player::add_exp(int e){
    experience += e;
    std::cout << "You gained " << e << " experience!" << std::endl;
    if(experience >= next_level){
      experience -= next_level;
      next_level = 100 * ++level;
      std::cout << "You leveled up! Now at level " << level << std::endl;
    }
    std::cout << next_level - experience << " experience until the next level" << std::endl;
}

Item* Player::get_item(std::string s){
  for(int i = 0; i < inventory.size(); i++){
    std::string n = inventory[i].get_name();
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    if(n == s){
      return &inventory[i];
    }
  }
  std::cout << "Sorry. That item is not in your inventory" << std::endl;
  return nullptr;
}

void Player::use_item(Item *a, WINDOW * win){
  //empty pointer
  if(!a){
    return;
  }
  int s = a->get_stat();
  Item I;
  switch(a->get_type()){
    case Potion:
      if(health == max_health){
        waddstr(win, "Already at max health");
        wrefresh(win);
        break;
      }
      health = (health + s > max_health) ? max_health : health + s;
      remove_item(a->get_name());
      break;
    case Weapon:
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
  std::string m = "Using item " + a->get_name();
  waddstr(win, m.c_str());
  wrefresh(win);
}

void Player::add_item(Item d){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() == d.get_name()){
      quantity[i]++;
      return;
    }
  }
  inventory.push_back(d);
  quantity.push_back(1);
}

void Player::remove_item(std::string s){
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
}

void Player::battle(Enemy &E, WINDOW * win){
  system("clear");
  std::string s;
  s = "You are attack by " + E.get_description() + "\n";
  waddstr(win, s.c_str());
  char ch;
  int x = 0;
  int y = 0;
  while(is_alive() && E.is_alive()){
    waddstr(win, "What would you like to do?");
    std::string s;
    while(1){
      ch = wgetch(win);
      //wmove(main, y, ++x);
      if(ch == '\n'){
        x = 0;
        waddch(win, ch);
        wmove(win, ++y, x);
        break;
      }
      else if((int)ch == KEY_BACKSPACE || (int)ch == KEY_DC){
        ch = '\b';
        waddch(win, ch);
        return;
      }
      //waddch(main, ch);
      s.push_back(ch);
    }
    if(s == "Use Item"){
      waddstr(win, "Which item would you like to use?\n");
      print_inventory();
      std::string c;
      std::getline(std::cin, c);
      Item *I = get_item(c);
      //nullprt if no item c in inventory
      if(!I){
        continue;
      }
      use_item(I, win);
      defend(E.attack());
    }
    else if (s == "attack"){
      if(get_speed() >= E.get_speed()){
        E.defend(attack());
        defend(E.attack());
      }
      else{
        defend(E.attack());
        E.defend(attack());
      }
    }
    else {
      waddstr(win, "Not a valid option");
      continue;
    }

  }

  //Player is dead
  if(!is_alive())
    return;

  add_exp(E.drop_exp());

  if(E.drop_loot())
    add_item(E.get_loot());
}
