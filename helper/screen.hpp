#include <ncurses.h>
#include <string>
#include <vector>

std::string select(WINDOW * win, std::vector<std::string> choices, int &y, bool vertical);
std::string get_line(WINDOW * win, int &y);
