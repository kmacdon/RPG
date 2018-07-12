#include "player.hpp"
#include <iostream>

Player::Player(){

}

Player::Player(std::string n, int h, int mh, int s[4], Item w, Item a){
    name = n;
    health = h;
    max_health = mh;
    assign(skills, s, sizeof(s)/sizeof(*s));
    weapon = w;
    armor = a;
    inventory[0] = weapon;
    inventory[1] = armor;
    quantity[0] = 1;
    quantity[1] = 1;
    alive = true;
    level = 1;
    experience = 0;
    next_level = 100;
}

Player::~Player(){

}

void Player::move(){
  std::cout << "Where would you like to go to next?\n";
  current.print_connections();
  std::string s;
  std::getline(std::cin, s);
  Location *L = current->get_connection(s);
  if(!L){
    return;
  }
  current = L;
}

void Player::set_location(Location* L){
  current = L;
}

Item Player::get_item(std::string s){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() == s){
      return inventory[i];
    }
  }
  std::cout << "Sorry. That item is not in your inventory" << std::endl;
  return Item();
}
void Player::use_item(Item *a){
  int s = item.get_stat();
  if(a.get_type() == "potion"){
    health = (health + s > max_health) ? max_health : health + s;
  }
  else if(a.get_type() == "weapon"){
    Item w = weapon;
    weapon = *a;
    *a = w;
  }
  else{
    Item d = armor;
    armor = *a;
    *a = d;
  }
}

void Player::battle(Enemy &E){
  std::cout << E.get_description() << std::endl;

  while(this->is_alive() && E.is_alive()){
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "Attack\tUse Item" << std::endl;
    std::string s;
    std::getline(std::cin, s);

    if(s == "Use Item"){
      std::cout << "Which item would you like to use?" << std::endl;
      this->print_inventory();
      std::string c;
      std::getline(std::cin, c);
      Item i = this->get_item();
      if(!i.get_stat()){
        continue;
      }
      this->use_item(i);
      this->defend(E.attack());
    }
    else if (s == "attack"){
      if(speed >= E.get_speed()){
        E.defend(this->attack());
      }
      else{
        this->defend(E.attack());
      }
    }
    else {
      std::cout << "Not a valid option" << std::endl;
      continue;
    }
  }
  if(!this->is_alive()){
    return;
  }
  this->add_exp(E.drop_exp());
  this->add_item(E.drop_loot());
}

void Player::print_stats(){
  this->Character::print_stats;
  std::cout << "Experience: " << experience << "\tNext Level: " << next_level << std::endl;
}
void Player::print_inventory(){
  for(int i = 0; i < inventory.size(); i++){
    std::cout << inventory[i] << std::endl;
  }
}

void Player::add_exp(int e){
    experience += e;
    std::cout << "You gained" << e << " experience!" << std::endl;
    if(experience >= next_level){
      experience = 0;
      level++;
      next_level = 100*level;
      std::cout << "You leveled up! Now at level " << level << std::endl;
    }
    std::cout << next_level - experience << " experience until the next level" << std::endl;
}

void Player::add_item(Item d){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() == d.get_name()){
      quantity[i]++;
      return
    }
  }
  inventory.push_back(d);
}

void Player::remove_item(std::string s){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() ==  s){
      inventory.erase(inventory.begin() + i);
      quantity[i] -= 1;
      break;
    }
  }
}
