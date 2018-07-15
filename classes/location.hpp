#include <string>
#include <vector>
#include "json_conversion.hpp"

class Enemy;

#pragma once
class Location{
private:
  friend class Game;
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
  void list_enemies();
  friend void to_json(nlohmann::json& j, const Location& L);
  friend void from_json(const nlohmann::json& j, Location& L);
};
