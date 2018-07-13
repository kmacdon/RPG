#include "enemy.hpp"
#include "../functions.hpp"

Enemy::Enemy(){
  name = "enemy";
  int s[4] = {1, 1, 1, 1};
  assign(skills, s, 4);
  weapon = Item("hand", "weapon", 1);
  armor = Item("clothes", "armor", 1);
  loot = Item("coins", "money", 1);
  loot_rate = 0;
  experience = 1;
}

Enemy::Enemy(std::string n){
  name = n;
  if(n == "wolf"){
    int s[4] = {2, 2, 3, 1};
    assign(skills, s, 4);
    weapon = Item("claws", "weapon", 2);
    armor = Item("fur", "armor", 2);
    loot = Item("coin", "money", 1);
    description = "wolf";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "bear"){
    int s[4] = {2, 2, 3, 1};
    assign(skills, s, 4);
    weapon = Item("claws", "weapon", 4);
    armor = Item("fur", "armor", 4);
    loot = Item("coin", "money", 1);
    description = "bear";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "goblin"){
    int s[4] = {2, 2, 3, 1};
    assign(skills, s, 4);
    weapon = Item("dagger", "weapon", 2);
    armor = Item("rusty mail", "armor", 2);
    loot = Item("coin", "money", 1);
    description = "goblin";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "orc"){
    int s[4] = {2, 2, 3, 1};
    assign(skills, s, 4);
    weapon = Item("broadsword", "weapon", 2);
    armor = Item("heavy mail", "armor", 2);
    loot = Item("coin", "money", 1);
    description = "orc";
    experience = 1;
    loot_rate = .05;
  }
  else{

  }
}

Enemy::Enemy(std::string n, int s[4]){
  assign(skills, s, 4);
  weapon = Item("claws", "weapon", 2);
  armor = Item("fur", "armor", 2);
  loot = Item("coin", "money", 1);
  description = "wolf";
  experience = 1;
  loot_rate = .05;
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

bool Enemy::drop_loot(){
  return (float)rand()/(float)(RAND_MAX) < loot_rate;
}

Item Enemy::get_loot(){
  std::cout << "Acquired: " << loot << std::endl;
  return loot;
}

std::string Enemy::get_description(){
  return description;
}
