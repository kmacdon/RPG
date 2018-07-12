#include "game.hpp"
#include <iostream>

Game::Game(){

}

Game::~Game(){

}

void Game::initialize(){
  std::cout << "Enter name: ";
  std::cin >>
}

//use srand(time(0))
Enemy Game::generate_enemy(std::string e[]){
  s = sizeof(e)/sizeof(*e);
  return Enemy(e[rand() % s]);
}
