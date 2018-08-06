#include "location.hpp"
#include <cstdlib>
#include <iostream>
#include "enemy.hpp"
#include "player.hpp"
#include "../data/constants.hpp"
#include "../helper/error.hpp"
#include <fstream>
//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Location::Location(){
  name = "NULL";
}

Location::Location(std::string n, float er, std::vector<std::string> e){
  name = n;
  encounter_rate = er;
  enemies = e;
}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

void Location::change_location(WINDOW * win, WINDOW * stats, Player *P, std::string s){
  bool change = false;
  std::vector<std::string> c = list_connections();
  for(int i = 0; i < c.size(); i++){
    if(c[i] == s){
      print_log(MAIN_LOG, "Moving from " + get_name() + " to " + c[i]);
      P->set_location(get_connection(c[i]));
      change = true;
      wrefresh(win);

      break;
    }
    if(i == c.size() - 1  && !change){
      waddstr(win, "Sorry, that is not a valid location\n");
      wrefresh(win);
      break;
    }
  }
  if(change && random_encounter()){
    wclear(win);
    P->battle(generate_enemy(), win, stats);
  }
}

void Location::add_connections(std::vector<Location *> c){
  connections.resize(c.size());
  connections = c;
}
//need to add srand(time(0)) when program starts

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
  return 0;
}

std::vector<std::string> Location::list_connections(){
  std::vector<std::string> s;
  for(int i = 0; i < connections.size(); i++){
    s.push_back(connections[i]->get_name());
  }
  return s;
}

bool Location::random_encounter(){
  return (float)rand()/(float)(RAND_MAX) < encounter_rate;
}

Enemy Location::generate_enemy(){
  int r = rand() % enemies.size();
  return load_enemy(enemies[r]);
}

Enemy Location::load_enemy(std::string e){
  print_log(MAIN_LOG, "Loading enemy " + e);
  std::ifstream input(ENEMY_FILE);
  nlohmann::json j;
  while(input >> j){
    if(j["object"] == "END"){
      break;
    }
    print_log(MAIN_LOG, j["name"]);
    if(j["name"] == e){
      print_log(MAIN_LOG, "Loaded enemy " + e);
      Enemy E = j;
      return E;
    }
  }
  std::string s = j["name"];
  print_log(MAIN_LOG, "Error: Failed to load enemy " + s);
  Enemy E;
  return E;
}
