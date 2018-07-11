#include "character.hpp"
#include "item.hpp"

class Enemy: public Character{
  Item loot;
  float loot_rate;
  int exp;
  char description[];
  //methods

  virtual void die();

public:
  Enemy();
  Enemy(char t[]);
  //redo this as inherited from characters
  Enemy(char t[], int h, int mh, int s[], Item w, int a, Item a, Item l[], float lr, char d[]);
  Item drop_loot();
  int drop_exp();
  char[] get_description();
  float get_loot_rate();
};
