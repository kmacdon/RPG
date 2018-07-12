#include "character.hpp"
#include "../functions.hpp"
#include <cmath>
#include <iostream>

Character::Character(){
  name = "C";
  health = 1;
  max_health = 1;
  int s[4] = {1, 1, 1, 1};
  assign(skills, s, 4);
  weapon = Item("axe", "weapon", 5);
  armor = Item("iron mail", "armor", 5);
  alive = true;
}

Character::Character(std::string n, int h, int mh, int s[4], int e, Item w, Item a){
    name = n;
    health = h;
    max_health = mh;
    assign(skills, s, 4);
    experience = e;
    weapon = w;
    armor = a;
    alive = true;
}

Character::~Character(){}

//maybe add random element to this and defend
int Character::attack(){
  std::cout << name << " attacks with " << weapon.get_name() << " and deals ";
  return round((.8*skills[0] + weapon.get_stat()));
}

void Character::defend(int a){
  int d = round(.7*skills[1] + armor.get_stat());
  d = (d > a) ? 1 : a - d;
  health -= d;
  std::cout << d << " points of damage!" << std::endl;
  if(health <= 0){
    alive = false;
    std::cout << name << " has died!" << std::endl;
  }
}

int Character::get_speed(){
  return skills[2];
}

void Character::print_stats(){
  std::cout << "Name: " << name << "\tHealth: " << health << "/" << max_health << std::endl;
  std::cout << "Weapon: " << weapon.get_name() << "\tArmor: " << armor.get_name() << std::endl;
  std::cout << "Str\tEnd\tSpd\tLck\n";
  std::cout << skills[0] << "\t" << skills[1] << "\t" << skills[2] << "\t" << skills[3] << std::endl;
}

bool Character::is_alive(){
  return alive;
}
