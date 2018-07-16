#include <ncurses.h>
#include "screen.hpp"
#include "../classes/player.hpp"
#include "../error.hpp"

void Screen::Inventory(Player *P){
  const std::string log_file = "log.txt";
  print_log(log_file, "Opening inventory screen", 0, false);
  char a = 'a';
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  //WINDOW * main = newwin(40, 40, 0, 0);

  int breaks[P->inventory.size()];
  int x = 0;
  int y = 0;
  //Display inventory screen and get selections
  while(1){
    print_log(log_file, "Entering Loop", 1);
    int ch;
    wmove(stdscr, 0, 0);
    if(P->inventory.size() == 0){
      waddstr(stdscr, "Your inventory is empty. Press \'q\' to exit.");
      wrefresh(stdscr);
      while(1){
        ch = getch();
        if(ch == 'q')
          break;
      }
      break;
    }

    //create inventory screen
    int breaks[P->inventory.size()];
    std::string a = "Inventory size: " + std::to_string(P->inventory.size());
    print_log(log_file, a, 1);
    for(int i = 0; i < P->inventory.size(); i++){
      waddstr(stdscr, P->inventory[i].get_name().c_str());
      waddch(stdscr, '\n');
      wmove(stdscr, i + 1, 0);
      breaks[i] = P->inventory[i].get_name().length();
      a = "Break " + std::to_string(i) + ": " + std::to_string(breaks[i]);
      print_log(log_file, a, 2);
      a = "Placing " + P->inventory[i].get_name() + " at position " + std::to_string(i) + ",0";
      print_log(log_file, a, 2);

    }
    if(y >= P->inventory.size()){
      print_log(log_file, "y > i", 2);
      y = 0;
    }
    wmove(stdscr, y, 0);

    print_log(log_file, "Inventory Printed", 2);
    a = "Current x = " + std::to_string(x);
    print_log(log_file, a, 2);
    a = "Current y = " + std::to_string(y);
    print_log(log_file, a, 2);

    wrefresh(stdscr);
    //wmove(stdscr, y, breaks[x]);
    ch = mvgetch(y, breaks[x]);

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
        wmove(stdscr, y, breaks[y]);
        break;
      case KEY_DOWN:
        print_log(log_file, "Input down", 3);
        y++;
        if(y >= P->inventory.size())
          y = P->inventory.size() - 1;
        v = "y = " + std::to_string(y);
        print_log(log_file, v, 3);
        wmove(stdscr, y, breaks[y]);
        break;
      //selection made
      case '\n':
          I = &P->inventory[y];
          v = "Selected " + I->get_name();
          print_log(log_file, v, 3);
        break;
      default:
        break;
    }
    if(I){
      wmove(stdscr, 0, 20);
      P->use_item(I);
      wrefresh(stdscr);
    }
    else if(ch == 'q'){
      break;
    }
    wrefresh(stdscr);
    wclear(stdscr);
  }

  endwin();
}
