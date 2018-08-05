#include "enemy.hpp"

//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Enemy::Enemy(){
  name = "enemy";
  skills["STR"] = 1;
  skills["END"] = 1;
  skills["SPD"] = 1;
  skills["LCK"] = 1;
  weapon = Item("hand", Weapon, 1);
  armor = Item("clothes", Armor, 1);
  loot = Item("coins", Money, 1);
  loot_rate = 0;
  experience = 1;
}

Enemy::Enemy(std::string n, std::unordered_map <std::string, int> s){
  skills = s;
  weapon = Item("claws", Weapon, 2);
  armor = Item("fur", Armor, 2);
  loot = Item("coin", Money, 1);
  description = "wolf";
  experience = 1;
  loot_rate = .05;
}

Enemy::Enemy(std::string n, int h, int mh, std::unordered_map <std::string, int> s, int e, Item w, Item a, Item l, float lr, std::string d){
  name = n;
  health = h;
  max_health = mh;
  skills = s;
  weapon = w;
  experience = e;
  armor = a;
  loot = l; //could replace this with char and use create_item function to save space
  loot_rate = lr;
  description = d;
}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

bool Enemy::drop_loot(){
  return (float)rand()/(float)(RAND_MAX) < loot_rate;
}

Item Enemy::get_loot(){
  std::cout << "Acquired: " << loot << std::endl;
  return loot;
}
