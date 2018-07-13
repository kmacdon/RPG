#include <string>
#include <vector>
#include "enemy.hpp"



#pragma once

class Location{
private:
  std::vector<Location *> connections;
  float encounter_rate;
  std::vector<std::string> enemies; //save memory and reduce dependencies
  std::string description;
protected:
  std::string name;
public:
  //methods
  Location();
  Location(std::string n, float er, std::vector<std::string> e);
  ~Location();
  void add_connections(std::vector<Location *> c);
  bool random_encounter();
  Enemy generate_enemy();
  std::string get_name();
  void print_connections();
  void set_connection(Location* L);
  int num_connections();
  Location* get_connection(std::string s);
  std::vector<std::string> list_connections();
  std::string get_description();
  friend std::string compress(Location L);
};
