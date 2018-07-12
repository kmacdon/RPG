#include "location.hpp"
#include "../functions.hpp"
#include <cstdlib>
#include <iostream>

Location::Location(){
  name = "NULL";
}

Location::Location(std::string n, float er, std::vector<std::string> e){
  name = n;
  encounter_rate = er;
  enemies = e;
  //likely size issues here

}

Location::~Location(){

}

void Location::add_connections(std::vector<Location *> c){
  connections.resize(c.size());
  assign(connections, c);
}
//need to add srand(time(0)) when program starts
bool Location::random_encounter(){
  return (float)rand()/(float)(RAND_MAX) < encounter_rate;
}

void Location::print_connections(){
  for(int i = 0; i < connections.size(); i++){
    std::cout << connections[i]->get_name() << std::endl;
  }
}

Location* Location::get_connection(std::string s){
  for(int i = 0; i < connections.size(); i++){
    if(connections[i]->get_name() == s){
      return connections[i];
    }
  }
  std::cout << "Sorry. That is not a viable location." << std::endl;
  return 0;
}
std::vector<std::string> Location::list_connections(){
  std::vector<std::string> s;
  for(int i = 0; i < connections.size(); i++){
    s.push_back(connections[i]->get_name());
  }
  return s;
}

Enemy Location::generate_enemy(){
  int r = rand() % enemies.size();
  return Enemy(enemies[r]);
}

std::string Location::get_name(){
  return name;
}

std::string Location::get_description(){
  return description;
}
