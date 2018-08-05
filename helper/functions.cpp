#include "functions.hpp"
#include <sstream>

std::vector <std::string> split(std::string s, char delim){
  std::stringstream info(s);
  std::string item;
  std::vector <std::string> items;
  while(getline(info, item, delim)){
    items.push_back(item);
  }
  return items;
}
