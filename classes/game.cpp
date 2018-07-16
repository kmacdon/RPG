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
  //welcome screen and player info
  std::string s;
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

void Game::inventory_screen(WINDOW * win){
    const std::string log_file = "log.txt";
    print_log(log_file, "Opening inventory screen", 0, false);
    char a = 'a';
    initscr();
    cbreak();
    noecho();
    keypad(win, TRUE);
    //WINDOW * main = newwin(40, 40, 0, 0);

    int breaks[P.inventory.size()];
    int x = 0;
    int y = 0;
    //Display inventory screen and get selections
    while(1){
      print_log(log_file, "Entering Loop", 1);
      int ch;
      wmove(win, 0, 0);
      if(P.inventory.size() == 0){
        waddstr(win, "Your inventory is empty. Press \'q\' to exit.");
        wrefresh(win);
        while(1){
          ch = wgetch(win);
          if(ch == 'q')
            break;
        }
        break;
      }

      //create inventory screen
      int breaks[P.inventory.size()];
      std::string a = "Inventory size: " + std::to_string(P.inventory.size());
      print_log(log_file, a, 1);
      for(int i = 0; i < P.inventory.size(); i++){
        waddstr(win, P.inventory[i].get_name().c_str());
        waddch(win, '\n');
        wmove(win, i + 1, 0);
        breaks[i] = P.inventory[i].get_name().length();
        a = "Break " + std::to_string(i) + ": " + std::to_string(breaks[i]);
        print_log(log_file, a, 2);
        a = "Placing " + P.inventory[i].get_name() + " at position " + std::to_string(i) + ",0";
        print_log(log_file, a, 2);
      }
      if(y >= P.inventory.size()){
        print_log(log_file, "y > i", 2);
        y = 0;
      }
      wmove(win, y, 0);

      print_log(log_file, "Inventory Printed", 2);
      a = "Current x = " + std::to_string(x);
      print_log(log_file, a, 2);
      a = "Current y = " + std::to_string(y);
      print_log(log_file, a, 2);

      wrefresh(win);
      //wmove(win, y, breaks[x]);
      ch = mvwgetch(win, y, breaks[x]);

      Item *I = nullptr;
      //Get input
      std::string v;

      //key selection
      switch (ch){
        case KEY_LEFT:
          break;
        case KEY_RIGHT:
          break;
        case KEY_UP:
          print_log(log_file, "Input up", 3);
          y--;
          if(y <= 0)
            y = 0;
          v = "y = " + std::to_string(y);
          print_log(log_file, v, 3);
          wmove(win, y, breaks[y]);
          break;
        case KEY_DOWN:
          print_log(log_file, "Input down", 3);
          y++;
          if(y >= P.inventory.size())
            y = P.inventory.size() - 1;
          v = "y = " + std::to_string(y);
          print_log(log_file, v, 3);
          wmove(win, y, breaks[y]);
          break;
        //selection made
        case '\n':
            I = &P.inventory[y];
            v = "Selected " + I->get_name();
            print_log(log_file, v, 3);
          break;
        default:
          break;
      }
      if(I){
        wmove(win, 0, 20);
        P.use_item(I, win);
        wrefresh(win);
      }
      else if(ch == 'q'){
        break;
      }
      wrefresh(win);
      wclear(win);
    }
    echo();
    nocbreak();
    endwin();
}

void Game::main_screen(){
  initscr();
  WINDOW * main = newwin(80, 50, 0, 0);
  WINDOW * info = newwin(5, 19, 0, 61);
  WINDOW * map = newwin(74, 19, 6, 61);
  keypad(main, TRUE);
  nocbreak();
  echo();
  std::string log_file = "log.txt";
  int x = 0;
  int y = 0;
  print_log(log_file, "Beginning loop", 0, false);

  //Refresh map
  map_screen(map);
  wrefresh(map);
  while(P.is_alive() && play_game){
    //Refresh stats
    P.print_stats(info);
    wrefresh(info);



    std::string a = "x = " + std::to_string(x) + " y = " + std::to_string(y);
    print_log(log_file, a, 1);
    x = 0;
    wmove(main, y, x);
    waddstr(main, "What would you like to do?");
    ++y;
    a = "x = " + std::to_string(x) + " y = " + std::to_string(y);
    print_log(log_file, a, 1);
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
      inventory_screen(main);
      wclear(main);
    }
    //change locations
    else if(v[0] == "move"){
      bool change = false;
      for(int i = 2; i < v.size(); i++){
        v[1] += v[i];
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
          P.battle(E, main);
        }
        map_screen(map);
        wrefresh(map);
      }

    }
    //save
    else if(v[0] == "save"){
      save();
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
      std::ifstream input("help.txt");
      while(std::getline(input, s)){
        waddstr(main, s.c_str());
      }
      input.close();
    }
    else{
      waddstr(main, "Sorry, that command is not recognized");
    }
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
  std::string b = "Current: " + P.current->get_name() + "\n";
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
  main_screen();
}

void Game::start(){
  system("clear");
  std::string s;
  std::ifstream input("data/welcome.txt");
  while(std::getline(input, s)){
    std::cout << s << std::endl;
  }
  input.close();
  //include option to reload
  while(play_game){
    initialize();
    play();
    if(reload)
      play_game = true;
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
