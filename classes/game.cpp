#include "game.hpp"
#include <fstream>
#include <algorithm>
#include "../functions.hpp"
#include "../error.hpp"


Game::Game(){
  play_game = true;
  P = Player();
}

Game::~Game(){

}

//create game instance
void Game::initialize(bool reload){
  srand(time(0));
  std::string log_file = "/Users/KevinMacDonald/Dropbox/Programming/CPP/RPG/log.txt";
  print_log(log_file, "Initializing");
  //Load data
  std::string filename;
  if(reload){
    filename = "/Users/KevinMacDonald/Dropbox/Programming/CPP/RPG/save.txt";
  }
  else{
    filename = "/Users/KevinMacDonald/Dropbox/Programming/CPP/RPG/default.txt";
  }
  load_data(filename);
  while(1){
    std::cout << "What is your name?" << std::endl;
    std::string s;
    std::getline(std::cin, s);
    if(s != "NULL"){
      break;
    }
    std::cout << "Sorry, that is not a valid name" << std::endl;
  }

  print_log(log_file, "Initialized");
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

void Game::play(){
  while(P.is_alive() && play_game){
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "Inventory\tMove\tStats\tSave\tQuit" << std::endl;
    std::string s;
    std::getline(std::cin, s);
    if(s == "Inventory"){
      P.print_inventory();
      std::cout << "use equip <item> to equip or quit to exit." << std::endl;
      std::getline(std::cin, s);
      std::vector<std::string> v = split(s, ' ');
      if(v[0] == "compare"){
        std::cout << P.get_item(v[1]) << P.get_item(v[2]) << std::endl;
      }
      else if(v[0] == "equip"){
        Item *I = P.get_item(v[1]);
        if(!I){
          continue;
        }
        P.use_item(P.get_item(v[1]));
      }
      else if(v[0] == "quit"){

      }
      else {
        std::cout << "Sorry, that command is not recognized" << std::endl;
      }
    }
    else if(s == "Move"){
      P.move();
    }
    else if(s == "Stats"){
      P.print_stats();
    }
    else if(s == "Save"){
      save();
    }
    else if(s == "Quit"){
      play_game = false;
    }
    else{
      std::cout << "Sorry, that command is not recognized" << std::endl;
    }
  }

}

void Game::save(){
    std::string filename = "save.txt";
    std::cout << "Overwriting " << filename << std::endl;
    std::ofstream output(filename);
    if(!output)
      std::cout << "Error: File failed to open" << std::endl;
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
}

//load data from file
void Game::load_data(std::string s){
  std::string log_file = "/Users/KevinMacDonald/Dropbox/Programming/CPP/RPG/log.txt";
  print_log(log_file, "Loading Data ... ");
  std::ifstream input(s);
  if(!input){
    std::cout << "Error: File failed to open" << std::endl;
    return;
  }
  nlohmann::json object;
  //get input
  int i = 0;
  while(input >> object){
    print_log(log_file, "Loading Object " + std::to_string(i++));
    //print_log(log_file, object.get<std::string>());
    if(object["object"] == "Location"){
      print_log(log_file, "Loading Location");
      Location L = object;
      print_log(log_file, "Location Loaded");
      map.push_back(L);
      print_log(log_file, "Map added to");
    }
    else if(object["object"] == "Player"){
      print_log(log_file, "Loaded Player");
      P = object;
      print_log(log_file, "Player Loaded");
    }
    else if(object["object"] == "END"){
      print_log(log_file, "End of Data");
      break;
    }
  }
  //create_map();
  print_log(log_file, "Closing input file");
  input.close();
  print_log(log_file, "Complete");
}

void Game::get_map(){
  for(int i = 0; i < map.size(); i++){
      std::cout << map[i].get_name() << std::endl;
  }
}

int Game::status(bool print){
  if(!print){

  }
  std::cout << "Play: " << play_game << std::endl;
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
