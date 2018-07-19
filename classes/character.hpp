#include "item.hpp"
#include <ncurses.h>
#pragma once

class Character{
protected:
  //Members
  int health;
  int max_health;
  int skills[4]; // Strength, Endurance, Speed, Luck
  int experience;
  Item weapon;
  Item armor;
  std::string name;
  bool alive;

public:
  //Constructors
  Character();
  Character(std::string n, int h, int mh, int s[4], int e, Item w, Item a);
  ~Character();

  //Methods
  std::string get_name() {return name;};
  int attack(WINDOW * win);
  void defend(WINDOW * win, int a);
  int get_speed() {return skills[2];};
  bool is_alive() {return alive;};

};
