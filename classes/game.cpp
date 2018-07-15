#include "game.hpp"
#include <fstream>
#include <algorithm>
#include "../functions.hpp"

//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Game::Game() :play_game(true), NAME_LENGTH(50),
SAVE_FILE("data/save.txt"),
LOG_FILE("log.txt"),
DEFAULT_FILE("data/default.txt"),
MAP_FILE("data/map.txt"){
  P = Player();
}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

//create game instance
void Game::initialize(bool reload){
  srand(time(0));
  //Load data
  std::string filename;
  if(reload){
    filename = SAVE_FILE;
  }
  else{
    filename = DEFAULT_FILE;
  }
  load_data(filename);
  create_map();
  //welcome screen and player info
  std::string s;
  std::ifstream input("data/welcome.txt");
  while(std::getline(input, s)){
    std::cout << s << std::endl;
  }
  input.close();
  while(1){

    std::cout << "What is your name?" << std::endl;
    std::getline(std::cin, s);
    if(s != "NULL" && s.length() < NAME_LENGTH){
      break;
    }
    std::cout << "Sorry, that is not a valid name" << std::endl;
  }
  std::cout << "Welcome " << s << std::endl;
  P.set_name(s);
}

//load data from file
void Game::load_data(std::string s){
  std::ifstream input(s);
  if(!input){
    std::cout << "Error: File " << s << " failed to open" << std::endl;
    return;
  }
  nlohmann::json object;
  //get input
  int i = 0;
  while(input >> object){
    if(object["object"] == "Location"){
      Location L = object;
      map.push_back(L);
    }
    else if(object["object"] == "Player"){
      P = object;
    }
    else if(object["object"] == "END"){
      break;
    }
  }
  //create_map();
  input.close();
}

//add connections between locations in map
void Game::create_map(){
  std::ifstream input(MAP_FILE);
  nlohmann::json j;

  while(input >> j){

    //create vector of pointers to locations and map them
    if(j["object"] == "Mapping"){
      std::vector<std::string> v = j.at("connections").get<std::vector<std::string> >();
      std::vector<Location *> c;
      for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < map.size(); j++){
          if(v[i] == map[j].get_name()){
            c.push_back(&map[j]);
          }
        }
      }

      //add pointers to location
      std::string name = j.at("name").get<std::string>();
      for(int i = 0; i < map.size(); i++){
        if(map[i].get_name() == name){
          map[i].add_connections(c);
        }
      }
    }
    else if(j["object"] == "P_Location"){
      for(int i = 0; i < map.size(); i++){
        if(j["current"] == map[i].get_name()){
          P.set_location(&map[i]);
        }
      }
    }
    else if(j["object"] == "END"){
      return;
    }
    else{
      std::cout << "Data type not recognized in map.txt" << std::endl;
    }
  }
}

//loop that contains top level game
void Game::play(){
  while(P.is_alive() && play_game){
    std::cout << "What would you like to do?" << std::endl;
    std::string s;
    std::getline(std::cin, s);
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    std::vector<std::string> v = split(s, ' ');

    //inventory management
    if(v[0] == "inventory"){
      P.print_inventory();
    }
    //equip items
    else if(v[0] == "equip"){
      for(int i = 2; i < v.size(); i++){
        v[1] += " " + v[i];
      }
      Item *I = P.get_item(v[1]);

      if(!I){
        continue;
      }
      P.use_item(I);
    }
    //change locations
    else if(v[0] == "move"){
      P.move();
      if(P.current->random_encounter()){
        Enemy E = P.current->generate_enemy();
        P.battle(E);
      }
    }

    //view stats
    else if(v[0] == "stats"){
      P.print_stats();
    }

    //save
    else if(v[0] == "save"){
      save();
    }

    //quit game
    else if(v[0] == "quit"){
      play_game = false;
    }

    //invisible commands
    else if(v[0] == "whereami"){
      std::cout << P.current->get_name() << std::endl;
    }
    else if(v[0] == "whoami"){
      std::cout << P.get_name() << std::endl;;
    }
    else if(v[0] == "help"){
      std::ifstream input("help.txt");
      while(std::getline(input, s)){
        std::cout << s << std::endl;
      }
      input.close();
    }
    else{
      std::cout << "Sorry, that command is not recognized" << std::endl;
    }
  }

}

void Game::save(){
    std::string filename = SAVE_FILE;
    std::cout << "Overwriting " << filename << std::endl;
    std::ofstream output(filename);
    if(!output){
      std::cout << "Error: File " << filename << " failed to open" << std::endl;
      return;
    }

    nlohmann::json j;
    for(int i = 0; i < map.size(); i++){
      j = map[i];
      output << j << std::endl;
    }
    j = P;
    output << j << std::endl;
    nlohmann::json k;
    k["object"] = "END";
    output << k << std::endl;
    output.close();

    //Save map
    output.open(MAP_FILE);
    nlohmann::json j2;
    j2["object"] = "P_Location";
    j2["current"] = P.get_location()->get_name();
    output << j2 << "\n";
    nlohmann::json j3;

    for(int i = 0; i < map.size(); i++){
      std::vector<std::string> v;
      v = P.get_location()->list_connections();
      j3["object"] = "Mapping";
      j3["connections"] = v;
      output << j3 <<  std::endl;
    }
    output << k << std::endl;

    output.close();
}

//Print general game details for debugging
int Game::status(bool print){
  if(!print){

  }
  std::cout << "------------------" << std::endl;
  std::cout << "Play Status: " << play_game << std::endl;
  std::cout << "------------------" << std::endl;
  std::cout << "Player: " << P.get_name() << std::endl;
  std::cout << "------------------" << std::endl;
  std::cout << "Map size: " << map.size() << std::endl;
  for(int i = 0; i < map.size(); i++){
    std::cout << map[i].get_name();
    map[i].print_connections();
  }
  std::cout << "------------------" << std::endl;
  if(P.get_name() != "NULL"){
    std::cout << "Player: " << std::endl;
    P.print_stats();
  }
  return 1;
}
