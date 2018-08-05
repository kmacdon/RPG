#include "character.hpp"
#include <cmath>


//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Character::Character(){
  name = "NULL";
  health = 1;
  max_health = 1;
  skills.push_back(1); skills.push_back(1); skills.push_back(1); skills.push_back(1);
  weapon = Item("rusty axe", Weapon, 2);
  armor = Item("rusty mail", Armor, 2);
  alive = true;
}

Character::Character(std::string n, int h, int mh, std::vector <int> s, int e, Item w, Item a){
    name = n;
    health = h;
    max_health = mh;
    skills = s;
    experience = e;
    weapon = w;
    armor = a;
    alive = true;
}

Character::~Character(){}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

//attack and defend
int Character::attack(WINDOW * win){
  std::string s =  name + " attacks with " + weapon.get_name() + " and deals ";
  waddstr(win, s.c_str());
  int a = 0;
  //Luck factor
  if((float)rand()/(float)RAND_MAX < .05*skills[3])
    a = sqrt(skills[3]);
  return round((.8*skills[0] + weapon.get_stat() + a));
}

void Character::defend(WINDOW * win, int a){
  int d = round(.7*skills[1] + armor.get_stat());
  d = (d > a) ? 1 : a - d;
  health -= d;
  std::string s = std::to_string(d) + " points\nof damage!\n";
  waddstr(win, s.c_str());
  if(health <= 0){
    alive = false;
    s = name + " has died!\n";
    waddstr(win, s.c_str());
  }
}
