#include "error.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

void print_log(std::string f, std::string msg, int tabs, bool append){
  std::ofstream error_file;
  if(append){
    error_file.open(f, std::ios::app);
  }
  else {
    error_file.open(f);
  }

  //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  //time_t t = std::chrono::system_clock::to_time_t(now);
  //error_file << ctime(&t) << ": ";

  if(!error_file){
    std::cout << "Error: " << f << " failed to open." << std::endl;
    return;
  }

  std::string s;
  if(tabs > 0){
    for(int i = 0; i < tabs; i++){
      s += '\t';
    }
    msg = s + msg;
  }
  error_file << msg << std::endl;
  error_file.close();
}
