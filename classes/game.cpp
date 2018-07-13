#include "game.hpp"
#include <fstream>
#include <algorithm>
#include "../functions.hpp"

Game::Game(){
  play = true;
  P = Player();
}

Game::~Game(){

}

//create game instance
void Game::initialize(bool reload){
  srand(time(0));

  //Load data
  std::string filename;
  if(reload){
    filename = "../save.txt";
  }
  else{
    filename = "/Users/KevinMacDonald/Dropbox/Programming/CPP/RPG/default.txt";
  }
  load_data(filename);
}

Player Game::create_Player(std::string g){
  std::vector<std::string> v;
  v = split(g, ':');
  int h;
  int mh;
  int s[4];
  int nl;
  Item w;
  Item a;
  std::vector<std::string> e;

  //values are stored in type:value format
  for(int i = 0; i < v.size() - 1; i+=2){
    if(v[i] == "health"){
      h = std::stoi(v[i + 1]);
    }
    else if(v[i] == "max_health"){
      mh = std::stoi(v[i+1]);
    }
    else if(v[i] == "Str" || v[i] == "End" || v[i] == "Spd" || v[i] == "Lck"){
      if(v[i] == "Str")
        s[0] = std::stoi(v[i]);
      else if(v[i] == "End")
        s[1] = std::stoi(v[i]);
      else if(v[i] == "End")
        s[2] = std::stoi(v[i]);
      else
        s[3] = std::stoi(v[i]);
    }
    else if(v[i] == "next_level"){
      nl = std::stoi(v[i]);
    }
    else if(v[i] == "weapon"){
      std::vector<std::string> stats = split(v[i], '_');
      if(stats.size() != 3){
        std::cout << "Error: loading weapon " << v[i] << std::endl;
      }
      w = Item(stats[0], stats[1], std::stoi(stats[2]));
    }
    else if(v[i] == "armor"){
      std::vector<std::string> stats = split(v[i], '_');
      if(stats.size() != 3){
        std::cout << "Error: loading armor " << v[i] << std::endl;
      }
      a = Item(stats[0], stats[1], std::stoi(stats[2]));
    }
    else {
      std::cout << "Error: Invalid data type \'" << v[i] << "\'." << std::endl;
    }

  }
  std::string n;
  std::cout << "What is your name?" << std::endl;
  std::getline(std::cin, n);
  P = Player(n, h, mh, s, w, a, nl);
  P.set_location(&map[0]);
  return P;
}

void Game::create_map(){
  std::cout << "Create map" << std::endl;
  //randomly create connections for maps
  //select location
  for(int i = 0; i < map.size(); i++){
    //select connections to add
    std::cout << "Connecting map " << map[i].get_name() << std::endl;
    for(int j = map[i].num_connections(); j < 3; j++ ){

      std::cout << "\tSelecting Random map" << std::endl;
      //select random map
      int limit = 0;
      int a = i;
      while(a == i){
        a = rand() % map.size();
        if(limit++ == 100){
          std::cout << "Could not allocate all connections" << std::endl;
          break;
        }
        if(a == i){
          continue;
        }
        //ensure connection is new and empty
        if(map[a].num_connections() == 3){
          a = i;
          continue;
        }
        for(int l = 0; l < map[i].num_connections(); l++){
          if(map[l].get_name() == map[i].get_name()){
            a = i;
            break;
          }
        }
      }
      map[i].set_connection(&map[a]);
      map[a].set_connection(&map[i]);
      std::cout << "connection assigned" << std::endl;
    }

  }
}

//load data from file
void Game::load_data(std::string s){
  std::cout << "Loading Data ... ";
  std::ifstream input(s);
  std::string info;
  std::vector<std::string> v;
  if(!input){
    std::cout << "file failed to open" << std::endl;
    return;
  }

  //get input
  while(std::getline(input, info)){
    v = split(info, ',');
    if(v[0] == "Location"){
      v.erase(v.begin());
      for(int i = 0; i < v.size() - 1; i++){
        v[0] += (":" + v[i + 1]);
      }
      std::string param = v[0];
      map.push_back(create_Location(param));
    }
    else if(v[0] == "Player"){
      v.erase(v.begin());
      for(int i = 0; i < v.size() - 1; i++){
        v[0] += (":" + v[i + 1]);
      }
      std::string param = v[0];
      create_Player(param);
    }
  }
  //create_map();
  input.close();
  std::cout << "Complete" << std::endl;
}

Location Game::create_Location(std::string s){
  std::vector<std::string> v;
  v = split(s, ':');
  std::string n;
  float er;
  std::vector<std::string> e;

  //values are stored in type:value format
  for(int i = 0; i < v.size() - 1; i+=2){
    if(v[i] == "name"){
      n = v[i + 1];
    }
    else if(v[i] == "encounter_rate"){
      er = std::stof(v[i + 1]);
    }
    else if(v[i] == "enemy"){
      e.push_back(v[i+1]);
    }
    else{
      std::cout << "Error: Invalid data type \'" << v[i] << "\'." << std::endl;
    }
  }
  return Location(n, er, e);
}

void Game::get_map(){
  for(int i = 0; i < map.size(); i++){
      std::cout << map[i].get_name() << std::endl;
  }
}

int Game::status(bool print){
  if(!print){

  }
  std::cout << "Play: " << play << std::endl;
  std::cout << "------------------" << std::endl;
  std::cout << "Map size: " << map.size() << std::endl;
  for(int i = 0; i < map.size(); i++){
    std::cout << map[i].get_name();
    map[i].print_connections();
    std::cout << "\n................" << std::endl;
  }
  std::cout << "------------------" << std::endl;
  if(P.get_name() != "NULL"){
    std::cout << "Player: " << std::endl;
    P.print_stats();
  }
  return 1;
}
