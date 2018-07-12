#include "player.hpp"
#include "../functions.hpp"
#include <iostream>

Player::Player(){

}

Player::Player(std::string n, int h, int mh, int s[4], Item w, Item a){
    name = n;
    health = h;
    max_health = mh;
    assign(skills, s, 4);
    weapon = w;
    armor = a;
    inventory.resize(2);
    inventory[0] = weapon;
    inventory[1] = armor;
    quantity.resize(2);
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
  int s = a->get_stat();
  if(a->get_type() == "potion"){
    health = (health + s > max_health) ? max_health : health + s;
    remove_item(a->get_name());
  }
  else if(a->get_type() == "weapon"){
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
      Item i = get_item(c);
      if(!i.get_stat()){
        continue;
      }
      use_item(&i);
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
