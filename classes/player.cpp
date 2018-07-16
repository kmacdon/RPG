#include "player.hpp"
#include "../functions.hpp"
#include <ncurses.h>
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

void Player::print_stats(){
  Character::print_stats();
  std::cout << "Experience: " << experience << "\tNext Level: " << next_level << std::endl;
  std::cout << "Str: "<< skills[0] << "\tEnd: " << skills[1] << "\tSpd: " << skills[2];
  std::cout << "\tLck: " << skills[3] << std::endl;
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

void Player::use_item(Item *a){
  //empty pointer
  if(!a){
    return;
  }
  int s = a->get_stat();
  Item I;
  switch(a->get_type()){
    case Potion:
      if(health == max_health){
        waddstr(stdscr, "Already at max health");
        wrefresh(stdscr);
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
  waddstr(stdscr, m.c_str());
  wrefresh(stdscr);
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

void Player::battle(Enemy &E){
  system("clear");
  std::cout << "You are attack by " << E.get_description() << std::endl;

  while(is_alive() && E.is_alive()){
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "Attack\tUse Item" << std::endl;
    std::string s;
    std::getline(std::cin, s);

    if(s == "Use Item"){
      std::cout << "Which item would you like to use?" << std::endl;
      print_inventory();
      std::string c;
      std::getline(std::cin, c);
      Item *I = get_item(c);
      //nullprt if no item c in inventory
      if(!I){
        continue;
      }
      use_item(I);
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
      std::cout << "Not a valid option" << std::endl;
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
