#include "item.hpp"
#include <ncurses.h>
#include <vector>
#pragma once

class Character{
protected:
  //Members
  int health;
  int max_health;
  std::vector <int> skills; // Strength, Endurance, Speed, Luck
  int experience;
  Item weapon;
  Item armor;
  std::string name;
  bool alive;

public:
  //Constructors
  Character();
  Character(std::string n, int h, int mh, std::vector <int> s, int e, Item w, Item a);
  ~Character();

  //Methods
  std::string get_name() {return name;};
  int attack(WINDOW * win);
  void defend(WINDOW * win, int a);
  int get_speed() {return skills[2];};
  bool is_alive() {return alive;};

};
