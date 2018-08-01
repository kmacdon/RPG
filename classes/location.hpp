#include <string>
#include <vector>
#include "json_conversion.hpp"

class Enemy;

#pragma once
class Location{
private:
  friend class Game;

  //Members
  std::vector<Location *> connections;
  float encounter_rate;
  std::vector<std::string> enemies; //save memory and reduce dependencies
  std::string description;
  std::vector<std::string> poi;

protected:
  std::string name;

public:
  //Constructors
  Location();
  Location(std::string n, float er, std::vector<std::string> e);
  ~Location() {};

  //Members
  void add_connections(std::vector<Location *> c);
  void print_connections();
  Location* get_connection(std::string s);
  std::vector<std::string> list_connections();
  std::vector<std::string> list_poi() {return poi;};

  bool random_encounter();
  std::string generate_enemy();

  //Getters
  std::string get_name() {return name;};
  std::string get_description() {return description;};

  //Friend
  friend void to_json(nlohmann::json& j, const Location& L);
  friend void from_json(const nlohmann::json& j, Location& L);
};
