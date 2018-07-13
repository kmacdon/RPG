#include "classes/location.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "classes/player.hpp"

#pragma once

void assign(int a[], int b[], int size);
void assign(std::vector <Location *> &a, std::vector <Location *> b);
std::vector <std::string> split(std::string s, char delim);
std::string compress(Location L);
std::string compress(Player P);
