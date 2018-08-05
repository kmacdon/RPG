#include <string>
#include <vector>
#include "json_conversion.hpp"
#include <ncurses.h>

class Enemy;

#pragma once

class Location{
private:
  friend class Game;

  //Members
  std::vector<Location *> connections;
  float encounter_rate;
  std::vector<std::string> enemies; //save memory and reduce dependencies
  std::vector<std::string> poi;
  //Methods
  bool random_encounter();
  Enemy generate_enemy();
  std::vector<std::string> list_connections();
  Location* get_connection(std::string s);
  Enemy load_enemy(std::string s);
protected:
  std::string name;
  std::string description;

public:
  //Constructors
  Location();
  Location(std::string n, float er, std::vector<std::string> e);
  ~Location() {};

  //Members
  void change_location(WINDOW * win, WINDOW * stats, Player *P, std::string s);
  void add_connections(std::vector<Location *> c);
  void print_connections();

  std::vector<std::string> list_poi() {return poi;};

  //Getters
  std::string get_name() {return name;};
  std::string get_description() {return description;};

  //Friend
  friend void to_json(nlohmann::json& j, const Location& L);
  friend void from_json(const nlohmann::json& j, Location& L);
};
