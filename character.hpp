#include "item.hpp"

class Character{
protected:
  //members
  int health;
  int max_health;
  int skills[]; // Strength, Endurance, Speed, Luck
  Item weapon;
  Item armor;
  char name[];
  bool alive;

public:
  Character();
  Character(int h, int mh, int s[], Item w, Item a, char n[]);
  ~Character();
  //methods
  int attack();
  void defend(int a);
  virtual void die(); //make virtual function
  virtual print_stats();
  int get_speed();
  bool is_alive();

};
