#include "enemy.hpp"
#include "player.hpp"

class Location{
private:
  Location *connections[];
  float encounter_rate;
  char enemies[][]; //save memory
protected:
  char name[];
public:
  //methods
  Location();
  Location(char n[], Location *c[], float er, Enemy *e[]);
  ~Location();
  void random_encounter();
  void battle(Player P, Enemy E);
  char[] get_name();
  Enemy generate_enemy();
  Locations *[] get_connections();


}
