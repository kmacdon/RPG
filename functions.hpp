#include "classes/location.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "classes/player.hpp"
#include <nlohmann/json.hpp>

#pragma once

void assign(int a[], int b[], int size);
void assign(std::vector <Location *> &a, std::vector <Location *> b);
std::vector <std::string> split(std::string s, char delim);
nlohmann::json compress(Location L);
nlohmann::json compress(Player P);
