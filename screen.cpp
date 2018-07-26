#include "screen.hpp"
#include "error.hpp"
#include "data/constants.hpp"
//Used to select input with arrow keys
std::string select(WINDOW * win, std::vector<std::string> choices, int &y, bool vertical){
  print_log(MAIN_LOG, "Entering select()");
  cbreak();
  noecho();
  int x = 0;
  int breaks[choices.size()];
  int y2 = y;
  int min = y;
  for(int i = 0; i < choices.size(); i++){
    if(i == 0 || vertical){
      breaks[i] = choices[i].size();
    }
    else{
      breaks[i] = choices[i].size() + 2 + breaks[i-1];
    }
    waddstr(win, choices[i].c_str());
    if(vertical){
      wmove(win, ++y2, 0);
    }
    else{
      wmove(win, y2, breaks[i] + 2);
    }
  }

  wmove(win, y, breaks[0]);
  wrefresh(win);

  //get arrow key input and selection
  std::string selection;
  while(1){
    char ch = wgetch(win);
    switch((int) ch){
      case 4: //Left
        if(!vertical){
          if(x > 0)
          x--;
          wmove(win, y, breaks[x]);
        }
        break;
      case 5: //Right
        if(!vertical){
          if(x < choices.size())
          x++;
          wmove(win, y, breaks[x]);
        }
        break;
      case 2: //Down
        if(vertical){
          if(y < choices.size())
          y++;
          wmove(win, y, breaks[y-min]);
        }
        break;
      case 3: //Up
        if(vertical){
          if(y > min)
            y--;
          wmove(win, y, breaks[y-min]);
        }
        break;
      case 'q':
        echo();
        nocbreak();
        return "q";
        break;
      case '\n':
        echo();
        nocbreak();
        if(vertical)
          selection = choices[y-min];
        else
          selection = choices[x];
        wmove(win, ++y, 0);
        print_log(MAIN_LOG, "Selection made");
        return selection;
        break;
      default:
        break;
    }
  }
  echo();
  nocbreak();
  print_log(MAIN_LOG, "Exiting Loop in error");
  return "Error";
}

std::string get_line(WINDOW * win, int &y){
  print_log(MAIN_LOG, "Entering get_line()");
  char ch;
  std::string s;

  //get input
  while(1){
    ch = wgetch(win);
    if(ch == '\n'){
      waddch(win, ch);
      wmove(win, ++y, 0);
      break;
    }
    else if((int)ch == KEY_BACKSPACE || (int)ch == KEY_DC){
      ch = '\b';
      waddch(win, ch);
    }
    //waddch(win, ch);
    s.push_back(ch);
  }
  print_log(MAIN_LOG, "Exiting get_line()");
  return s;
}
