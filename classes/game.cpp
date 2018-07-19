#include "game.hpp"
#include <fstream>
#include <algorithm>
#include "../functions.hpp"
#include <ncurses.h>
#include "../error.hpp"
//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Game::Game() :play_game(true), reload(false),
NAME_LENGTH(50),
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
void Game::initialize(){
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
}

//load data from file
void Game::load_data(std::string s){

  print_log(LOG_FILE, "Load Data", 1, false);
  std::ifstream input(s);
  if(!input){
    std::cout << "Error: File " << s << " failed to open" << std::endl;
    return;
  }
  nlohmann::json object;
  //get input
  int i = 0;
  while(input >> object){
    if(object["object"] != "END"){
      std::string s = object.at("object").get<std::string>();
      print_log(LOG_FILE, s.c_str(), 1, false);
      s = object.at("name").get<std::string>();
      print_log(LOG_FILE, s.c_str(), 1, false);
    }

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

void Game::welcome_screen(WINDOW * win){
  //Welcome Screen
  int y = 0;
  std::string s;
  std::ifstream input("data/welcome.txt");
  while(std::getline(input, s)){
    waddstr(win, s.c_str());
    wmove(win, y++, 0);
  }
  input.close();

  //Player info
  //get input
  s.clear();
  wmove(win, ++y, 0);
  waddstr(win, "What is your name?");
  wmove(win, ++y, 0);

  int ch;
  while(1){
    while(1){
      ch = wgetch(win);
      //wmove(win, y, ++x);
      if(ch == '\n'){
        waddch(win, ch);
        wmove(win, ++y, 0);
        break;
      }
      else if((int)ch == KEY_BACKSPACE || (int)ch == KEY_DC){
        ch = '\b';
        waddch(win, ch);
        return;
      }
      //waddch(win, ch);
      s.push_back(ch);
    }
    if(s != "NULL" && s.length() < NAME_LENGTH){
      break;
    }
    waddstr(win, "Sorry, that is not a valid name.");
    wmove(win, ++y, 0);
  }
  P.set_name(s);
  s = "Welcome " + s;
  waddstr(win, s.c_str());
  wmove(win, ++y, 0);
}

void Game::inventory_screen(WINDOW * win){

}

void Game::main_screen(){
  initscr();
  WINDOW * main = newwin(80, 50, 0, 0);
  WINDOW * info = newwin(5, 19, 0, 61);
  WINDOW * map = newwin(74, 19, 6, 61);
  keypad(main, TRUE);
  nocbreak();
  echo();
  int x = 0;
  int y = 0;
  print_log(LOG_FILE, "Beginning loop", 0, false);
  welcome_screen(main);
  wrefresh(main);
  //start game
  int ch = wgetch(main);
  //Refresh map
  wclear(main);
  map_screen(map);
  wrefresh(map);
  while(P.is_alive() && play_game){
    if(y > 23){
      y = 0;
      wclear(main);
      wrefresh(main);
    }
    //Refresh stats
    P.print_stats(info);
    wrefresh(info);



    std::string a = "x = " + std::to_string(x) + " y = " + std::to_string(y);
    print_log(LOG_FILE, a, 1);
    x = 0;
    wmove(main, y, x);
    waddstr(main, "What would you like to do?");
    ++y;
    a = "x = " + std::to_string(x) + " y = " + std::to_string(y);
    print_log(LOG_FILE, a, 1);
    wmove(main, y, x);
    wrefresh(main);
    char ch;
    std::string s;

    //get input
    while(1){
      ch = wgetch(main);
      //wmove(main, y, ++x);
      if(ch == '\n'){
        x = 0;
        waddch(main, ch);
        wmove(main, ++y, x);
        break;
      }
      else if((int)ch == KEY_BACKSPACE || (int)ch == KEY_DC){
        ch = '\b';
        waddch(main, ch);
        return;
      }
      //waddch(main, ch);
      s.push_back(ch);
    }

    std::vector<std::string> v = split(s, ' ');
    std::transform(v[0].begin(), v[0].end(), v[0].begin(), ::tolower);
    //inventory management
    if(v[0] == "inventory"){
      wclear(main);
      P.print_inventory(main);
      wclear(main);
    }
    //change locations
    else if(v[0] == "move"){
      bool change = false;
      for(int i = 2; i < v.size(); i++){
        v[1] += " " + v[i];
      }
      std::vector<std::string> c = P.current->list_connections();
      for(int i = 0; i < c.size(); i++){
        if(c[i] == v[1]){
          P.current = P.current->get_connection(c[i]);
          change = true;
          wrefresh(main);
          break;
        }
        if(i == c.size() - 1  && !change){
          waddstr(main, "Sorry, that is not a valid location\n");
          wrefresh(main);
          break;
        }
      }
      if(change){
        if(P.current->random_encounter()){
          Enemy E = P.current->generate_enemy();
          wclear(main);
          P.battle(E, main);
        }
        wclear(map);
        map_screen(map);
        wrefresh(map);
      }

    }
    //save
    else if(v[0] == "save"){
      save(main);
    }
    //reload Save
    else if(v[0] == "reload"){
      play_game = false;
      reload = true;
    }
    //quit game
    else if(v[0] == "quit"){
      play_game = false;
    }

    //invisible commands
    else if(v[0] == "whereami"){
      waddstr(main, P.current->get_name().c_str());
    }
    else if(v[0] == "whoami"){
      waddstr(main, P.get_name().c_str());
    }
    else if(v[0] == "help"){
      wclear(main);
      std::ifstream input("help.txt");
      while(std::getline(input, s)){
        waddstr(main, s.c_str());
      }
      input.close();
    }
    else{
      waddstr(main, "Sorry, that command is not recognized");
    }
    wrefresh(main);
    y++;
    //wclear(main);
  }
  if(play_game && reload){
    waddstr(main, "Reloading last save");
    wrefresh(main);
  }
  endwin();
}

void Game::map_screen(WINDOW * win){
  wmove(win, 0, 0);
  std::vector<std::string> c = P.current->list_connections();
  std::string b = "Current: \n" + P.current->get_name() + "\n";
  waddstr(win, b.c_str());
  waddstr(win, "Connections: \n");
  for(int i = 0; i < c.size(); i++){
    b = "-" + c[i] + "\n";
    waddstr(win, b.c_str());
  }
}
//add connections between locations in map
void Game::create_map(){
  std::ifstream input(MAP_FILE);
  nlohmann::json j;
  print_log(LOG_FILE, "Loading Data", 0);
  while(input >> j){
    std::string a = j.at("object").get<std::string>();
    print_log(LOG_FILE, a.c_str(), 1);
    //create vector of pointers to locations and map them
    if(j["object"] == "Mapping"){
      std::string s = j.at("name").get<std::string>();
      print_log(LOG_FILE, s.c_str(), 0);
      std::vector<std::string> v = j.at("connections").get<std::vector<std::string> >();
      std::vector<Location *> c;
      //Loop through all connections listed
      for(int i = 0; i < v.size(); i++){
        //loop through all other maps
        for(int j = 0; j < map.size(); j++){
          //match the connection to the address of the location stored in map
          if(v[i] == map[j].get_name()){
            s = "Adding " + map[j].get_name();
            print_log(LOG_FILE, s.c_str(), 0);
            c.push_back(&map[j]);
          }
        }
      }

      //add pointers to location creating its connection
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
  main_screen();
}

void Game::start(){
  //include option to reload
  while(play_game){
    initialize();
    play();
    if(reload)
      play_game = true;
  }

}

void Game::save(WINDOW * win){
    std::string filename = SAVE_FILE;
    std::string s = "Overwriting " + filename;
    waddstr(win, s.c_str());
    std::ofstream output(filename);
    if(!output){
      s = "Error: File " + filename + " failed to open";
      waddstr(win, s.c_str());
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
      v = map[i].list_connections();
      j3["object"] = "Mapping";
      j3["connections"] = v;
      j3["name"] = map[i].get_name();
      output << j3 <<  std::endl;
    }
    output << k << std::endl;

    output.close();
}

//Print general game details for debugging
int Game::status(bool print){
  WINDOW * info = newwin(40, 20, 60, 0);
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
    P.print_stats(info);
  }
  return 1;
}
