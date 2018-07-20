#include "player.hpp"
#include "../functions.hpp"
#include "../error.hpp"
//////////////////////////////////////////////////////////////
//////////////////////  Constructors  ////////////////////////
//////////////////////////////////////////////////////////////

Player::Player(){
  name = "NULL";
}

Player::Player(std::string n, int h, int mh, int s[4], Item w, Item a, int next_level){
  name = n;
  health = h;
  max_health = mh;
  assign(skills, s, 4);
  weapon = w;
  armor = a;
  alive = true;
  level = 1;
  experience = 0;
  next_level = 100;
}

//////////////////////////////////////////////////////////////
//////////////////////  Methods  /////////////////////////////
//////////////////////////////////////////////////////////////

void Player::move(){
  current->print_connections();
  std::string s;
  std::getline(std::cin, s);
  std::vector<std::string> c = current->list_connections();
  for(int i = 0; i < c.size(); i++){
    if(c[i] == s){
      current = current->get_connection(s);
      return;
    }
  }
}

Location* Player::get_location(){
  return current;
}

void Player::set_location(Location* L){
  current = L;
}

void Player::print_stats(WINDOW * win){
  wmove(win, 0, 0);
  std::string s = "| Name: " + name + "\n";
  waddstr(win, s.c_str());
  s = "| Level: " + std::to_string(level) + "\n";
  waddstr(win, s.c_str());
  s = "| Health: " + std::to_string(health) + "/" + std::to_string(max_health) + "\n";
  waddstr(win, s.c_str());
  s = "| Experience: " + std::to_string(experience) + "\n| Next Level:" + std::to_string(next_level) + "\n";
  waddstr(win, s.c_str());
  s = "| Str: " + std::to_string(skills[0]) + "  End: " + std::to_string(skills[1]) + "\n| Spd: " + std::to_string(skills[2]);
  waddstr(win, s.c_str());
  s = "  Lck: " + std::to_string(skills[3]) + "\n";
  waddstr(win, s.c_str());
  waddstr(win, "|__________________");
}

void Player::add_exp(WINDOW * win, int e){
    experience += e;
    std::string s = "You gained " + std::to_string(e) + " experience!\n";
    waddstr(win, s.c_str());
    if(experience >= next_level){
      experience -= next_level;
      next_level = 100 * ++level;
      std::string s = "You leveled up! Now at level " + std::to_string(level);
      waddstr(win, s.c_str());
    }
    s = std::to_string(next_level - experience) + " experience until the next level";
    waddstr(win, s.c_str());
}

//Print out inventory
void Player::print_inventory(WINDOW * win){
  const std::string log_file = "log.txt";
  print_log(log_file, "Opening inventory screen", 0, false);
  char a = 'a';
  initscr();
  cbreak();
  noecho();
  keypad(win, TRUE);
  //WINDOW * main = newwin(40, 40, 0, 0);


  int x = 0;
  int y = 0;
  //Display inventory screen and get selections
  while(1){
    print_log(log_file, "Entering Loop", 1);
    int ch;
    wmove(win, 0, 0);
    if(inventory.size() == 0){
      waddstr(win, "Your inventory is empty. Press \'q\' to exit.");
      wrefresh(win);
      while(1){
        ch = wgetch(win);
        if(ch == 'q')
          break;
      }
      break;
    }

    //create inventory screen
    int breaks[inventory.size()];
    std::string a = "Inventory size: " + std::to_string(inventory.size());
    print_log(log_file, a, 1);
    for(int i = 0; i < inventory.size(); i++){
      waddstr(win, inventory[i].get_name().c_str());
      waddch(win, '\n');
      wmove(win, i + 1, 0);
      breaks[i] = inventory[i].get_name().length();
      a = "Break " + std::to_string(i) + ": " + std::to_string(breaks[i]);
      print_log(log_file, a, 2);
      a = "Placing " + inventory[i].get_name() + " at position " + std::to_string(i) + ",0";
      print_log(log_file, a, 2);
    }
    if(y >= inventory.size()){
      print_log(log_file, "y > i", 2);
      y = 0;
    }
    wmove(win, y, 0);

    print_log(log_file, "Inventory Printed", 2);
    a = "Current x = " + std::to_string(x);
    print_log(log_file, a, 2);
    a = "Current y = " + std::to_string(y);
    print_log(log_file, a, 2);

    wrefresh(win);
    //wmove(win, y, breaks[x]);
    ch = mvwgetch(win, y, breaks[x]);

    Item *I = nullptr;
    //Get input
    std::string v;

    //key selection
    switch (ch){
      case KEY_UP:
        print_log(log_file, "Input up", 3);
        y--;
        if(y <= 0)
          y = 0;
        v = "y = " + std::to_string(y);
        print_log(log_file, v, 3);
        wmove(win, y, breaks[y]);
        break;
      case KEY_DOWN:
        print_log(log_file, "Input down", 3);
        y++;
        if(y >= inventory.size())
          y = inventory.size() - 1;
        v = "y = " + std::to_string(y);
        print_log(log_file, v, 3);
        wmove(win, y, breaks[y]);
        break;
      //selection made
      case '\n':
          I = &inventory[y];
          v = "Selected " + I->get_name();
          print_log(log_file, v, 3);
        break;
      default:
        break;
    }
    if(I){
      wmove(win, 0, 20);
      use_item(I, win);
      wrefresh(win);
    }
    else if(ch == 'q'){
      break;
    }
    wrefresh(win);
    wclear(win);
  }
  echo();
  nocbreak();
  endwin();
}

Item* Player::get_item(WINDOW * win, std::string s){
  for(int i = 0; i < inventory.size(); i++){
    std::string n = inventory[i].get_name();
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    if(n == s){
      return &inventory[i];
    }
  }
  waddstr(win, "Sorry. That item is not in your inventory");
  return nullptr;
}

void Player::use_item(Item *a, WINDOW * win){
  //empty pointer
  if(!a){
    return;
  }
  int s = a->get_stat();
  Item I;
  switch(a->get_type()){
    case Potion:
      if(health == max_health){
        waddstr(win, "Already at max health");
        wrefresh(win);
        break;
      }
      health = (health + s > max_health) ? max_health : health + s;
      remove_item(a->get_name());
      break;
    case Weapon:
      I = weapon;
      weapon = *a;
      *a = I;
      break;
    case Armor:
      I = armor;
      armor = *a;
      *a = I;
      break;
    default:
      break;
  }
  std::string m = "Using item " + a->get_name();
  waddstr(win, m.c_str());
  wrefresh(win);
}

void Player::add_item(WINDOW * win, Item d){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() == d.get_name()){
      quantity[i]++;
      return;
    }
  }
  inventory.push_back(d);
  quantity.push_back(1);
}

void Player::remove_item(std::string s){
  for(int i = 0; i < inventory.size(); i++){
    if(inventory[i].get_name() ==  s){
      quantity[i]--;
      if(quantity[i] == 0){
        inventory.erase(inventory.begin() + i);
        quantity.erase(quantity.begin() + i);
      }
      break;
    }
  }
}

void Player::battle(Enemy &E, WINDOW * win){
  wclear(win);
  std::string s;
  s = "You are attacked by " + E.get_description() + "\n";
  waddstr(win, s.c_str());
  char ch;
  int x = 0;
  int y = 0;
  while(is_alive() && E.is_alive()){
    waddstr(win, "What would you like to do?");
    std::string s;
    while(1){
      ch = wgetch(win);
      //wmove(main, y, ++x);
      if(ch == '\n'){
        x = 0;
        waddch(win, ch);
        wmove(win, ++y, x);
        break;
      }
      else if((int)ch == KEY_BACKSPACE || (int)ch == KEY_DC){
        ch = '\b';
        waddch(win, ch);
        return;
      }
      //waddch(main, ch);
      s.push_back(ch);
    }
    if(s == "Use Item"){
      waddstr(win, "Which item would you like to use?\n");
      print_inventory(win);
      std::string c;
      std::getline(std::cin, c);
      Item *I = get_item(win, c);
      //nullprt if no item c in inventory
      if(!I){
        continue;
      }
      use_item(I, win);
      defend(win, E.attack(win));
    }
    else if (s == "attack"){
      if(get_speed() >= E.get_speed()){
        E.defend(win, attack(win));
        defend(win, E.attack(win));
      }
      else{
        defend(win, E.attack(win));
        E.defend(win, attack(win));
      }
    }
    else {
      waddstr(win, "Not a valid option");
      continue;
    }

  }

  //Player is dead
  if(!is_alive())
    return;

  add_exp(win, E.drop_exp());

  if(E.drop_loot())
    add_item(win, E.get_loot());
  wrefresh(win);
}
