#include "character.hpp"

class Player: public Character{
  int exp;
  int level;
  int next_level;
  Item inventory[];
  int quantity[];
  Location current;

  //methods
public:
  Player();
  ~Player();
  void move();
  void use_item();
  virtual void print_stats();
  void print_inventory();
  void add_exp(int e);
  void add_item(Item i);
  void remove_item(char n[]);
  virtual void die();

}
