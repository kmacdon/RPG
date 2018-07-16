#include "functions.hpp"

void assign(int a[], int b[], int size){
  for(int i = 0; i < size; i++){
    a[i] = b[i];
  }
}

void assign(std::vector <Location *> &a, std::vector <Location *> b){
  for(int i = 0; i < a.size(); i++){
     a[i] = b[i];
  }
}

std::vector <std::string> split(std::string s, char delim){
  std::stringstream info(s);
  std::string item;
  std::vector <std::string> items;
  while(getline(info, item, delim)){
    items.push_back(item);
  }
  return items;
}

std::string getstring(WINDOW * win){
  std::string s;
  int ch = wgetch(win);
  while(ch != '\n'){
    s.push_back(ch);
    ch = wgetch(win);
    if(ch == KEY_DC){
      s.erase(s.end()-1, s.end());
    }
  }
  return s;
}

std::ostream& unbold(std::ostream& os)
{
    return os << "\e[0m";
}

std::ostream& bold(std::ostream& os)
{
    return os << "\e[1m";
}
