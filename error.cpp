#include "error.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

void print_log(std::string filename, std::string msg, bool append){
  std::ofstream error_file;
  if(append){
    error_file.open(filename, std::fstream::app);
  }
  else{
    error_file.open(filename);
  }


  char s[1000];
  time_t t = time(NULL);
  struct tm * p = localtime(&t);
  strftime(s, 1000, "%B %d, %H:%M:%S", p);
  std::string a = s;
  if(!error_file){
    std::cout << "Error: " << filename << " failed to open.\n";
    return;
  }

  msg = a + " " + msg + "\n";
  error_file << msg;
  error_file.close();
}
