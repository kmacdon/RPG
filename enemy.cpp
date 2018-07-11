#include "enemy.hpp"
#include "functions.hpp"

Enemy::Enemy(){

}

Enemy::Enemy(char t[]){
  if(!strcmp(t, "wolf")){
    Enemy E(t, );
  }
  else if(!strcmp(t, "bear")){

  }
  else if(!strcmp(t, "goblin")){

  }
  else if(!strcmp(t, "orc")){

  }
}

Enemy::Enemy(char t[], int h, int mh, int s[], Item w, int e, Item a, Item l, float lr, char d[]){
  name = t;
  health = h;
  max_health = mh;
  assign(skills, s, sizeof(s)/sizeof(*s));
  weapon = w;
  exp = e;
  armor = a;
  loot = l; //could replace this with char and use create_item function to save space
  loot_rate = lr;
  //might run into issues here with length differences
  assign(description, d, sizeof(d)/sizeof(*d));
}

Enemy::~Enemy(){

}

int Enemy::drop_exp(){
  return exp;
}

Item Enemy::drop_loot(){
  return loot;
}

float Enemy::get_loot_rate(){
  return loot_rate;
}
