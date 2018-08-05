#include "enemy.hpp"
#include "../helper/functions.hpp"

//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Enemy::Enemy(){
  name = "enemy";
  skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
  weapon = Item("hand", Weapon, 1);
  armor = Item("clothes", Armor, 1);
  loot = Item("coins", Money, 1);
  loot_rate = 0;
  experience = 1;
}

Enemy::Enemy(std::string n){
  name = n;
  if(n == "wolf"){
    skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
    weapon = Item("claws", Weapon, 2);
    armor = Item("fur", Armor, 2);
    loot = Item("coin", Money, 1);
    description = "wolf";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "bear"){
    skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
    weapon = Item("claws", Weapon, 4);
    armor = Item("fur", Armor, 4);
    loot = Item("coin", Money, 1);
    description = "bear";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "goblin"){
    skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
    weapon = Item("dagger", Weapon, 2);
    armor = Item("rusty mail", Armor, 2);
    loot = Item("coin", Money, 1);
    description = "goblin";
    experience = 1;
    loot_rate = .05;
  }
  else if(n == "orc"){
    skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
    weapon = Item("broadsword", Weapon, 2);
    armor = Item("heavy mail", Armor, 2);
    loot = Item("coin", Money, 1);
    description = "orc";
    experience = 1;
    loot_rate = .05;
  }
  else{

  }
}

Enemy::Enemy(std::string n, std::vector <int> s){
  skills = s;
  weapon = Item("claws", Weapon, 2);
  armor = Item("fur", Armor, 2);
  loot = Item("coin", Money, 1);
  description = "wolf";
  experience = 1;
  loot_rate = .05;
}

Enemy::Enemy(std::string n, int h, int mh, std::vector <int> s, int e, Item w, Item a, Item l, float lr, std::string d){
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
