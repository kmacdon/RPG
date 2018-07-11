#include "location.hpp"
#include <cstdlib>
#include <iostream>

Location::Location(){

}

Location::Location(char n[], Location *c[], float er, char e[][]){
  name = n;
  assign(connections, c);
  encounter_rate = er;
  //likely size issues here
  assign(enemies, e, sizeof(e)/sizeof(*e));
}

//need to add srand(time(0)) when program starts
void Location::random_encounter(){
  //generate random enemy from list of possible enemies
  if((float)rand()/(float)(RAND_MAX) < encounter_rate){
    Enemy E  = current.generate_enemy();
    current.battle(P, E);
  }
}

Location *[] get_connections(){
  return connections;
}

void Location::battle(Player& P, Enemy& E){
  std::cout << E.get_description() << std::endl;
  while(P.is_alive() && E.is_alive()){
    //get input
    do {
      if(!strcmp(input, "use_item"){
        P.use_item();
      }
      else if (!strcmp(input, "attack"){
        break;
      } else {
        std::cout << "Not a valid option" << std::endl;
      }
    } while(strcmp(input, "attack"));


//size issues
Enemy Location::generate_enemy(){
  s = sizeof(enemies)/sizeof(*enemies);
  //create random enemy based on lsit
  Enemy E(enemies[rand() % s]);

  return E;
}
