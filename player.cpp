#include "player.hpp"
#include <iostream>

Player::Player(){
  //enter welcome stuff here
}

void Player::move(){
  std::cout << "Where would you like to go to next?\n";
  Location *list[] = current.get_connections();

  for(int i = 0; i < sizeof(list)/sizeof(*list)){
    std::cout << *list[i] << std::endl;
  }
  
}
