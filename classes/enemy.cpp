#include "enemy.hpp"
#include "../functions.hpp"

Enemy::Enemy(){
  name = "enemy";
  int s[4] = {1, 1, 1, 1};
  assign(this->skills, s, 4);
  weapon = Item("hand", "weapon", 1);
  armor = Item("clothes", "armor", 1);
  loot = Item("coins", "money", 1);
  loot_rate = 0;
  experience = 1;
}

Enemy::Enemy(std::string n){
  this->name = n;
  if(n == "wolf"){
    int s[4] = {2, 2, 3, 1};
    assign(this->skills, s, 4);
    this->weapon = Item("claws", "weapon", 2);
    this->armor = Item("fur", "armor", 2);
    this->loot = Item("coin", "money", 1);
    this->description = "wolf";
    this->experience = 1;
    this->loot_rate = .05;
  }
  else if(n == "bear"){
    int s[4] = {2, 2, 3, 1};
    assign(this->skills, s, 4);
    this->weapon = Item("claws", "weapon", 4);
    this->armor = Item("fur", "armor", 4);
    this->loot = Item("coin", "money", 1);
    this->description = "bear";
    this->experience = 1;
    this->loot_rate = .05;
  }
  else if(n == "goblin"){
    int s[4] = {2, 2, 3, 1};
    assign(this->skills, s, 4);
    this->weapon = Item("dagger", "weapon", 2);
    this->armor = Item("rusty mail", "armor", 2);
    this->loot = Item("coin", "money", 1);
    this->description = "goblin";
    this->experience = 1;
    this->loot_rate = .05;
  }
  else if(n == "orc"){
    int s[4] = {2, 2, 3, 1};
    assign(this->skills, s, 4);
    this->weapon = Item("broadsword", "weapon", 2);
    this->armor = Item("heavy mail", "armor", 2);
    this->loot = Item("coin", "money", 1);
    this->description = "orc";
    this->experience = 1;
    this->loot_rate = .05;
  }
  else{

  }
}

Enemy::Enemy(std::string n, int h, int mh, int s[4], int e, Item w, Item a, Item l, float lr, std::string d){
  name = n;
  health = h;
  max_health = mh;
  assign(skills, s, 4);
  weapon = w;
  experience = e;
  armor = a;
  loot = l; //could replace this with char and use create_item function to save space
  loot_rate = lr;
  description = d;
}

Enemy::~Enemy(){}

int Enemy::drop_exp(){
  return experience;
}

Item Enemy::drop_loot(){
  return loot;
}

float Enemy::get_loot_rate(){
  return loot_rate;
}

void Enemy::print_stats(){
  this->Character::print_stats();
  std::cout << "Experience: " << experience << "\tLoot: " << loot << std::endl;
  std::cout << this->description << std::endl;
}

std::string Enemy::get_description(){
  return description;
}
