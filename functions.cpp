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

//compress functions convert object to JSON
nlohmann::json compress(Location L){
  std::string s = "{ \"type\": \"Location\"";
  s = ",name\": \""+ L.get_name() + "\"";
  s += ",\"encounter_rate\": " + std::to_string(L.encounter_rate);
  for(int i = 0; i < L.enemies.size(); i++){
    s += ",enemy\": \"" + L.enemies[i] + "\"";
  }
  for(int i = 0; i < L.connections.size(); i++){
    s += ",\"connection\": \"" + L.connections[i]->get_name() + "\"";
  }
  s += " }";
  return nlohmann::json::parse(s);
}

nlohmann::json compress(Player P){
  std::string s = "{ \"type\": \"Player\"";
  s = ",\"name\": \"" + P.name + "\"";
  s += ",\"health\": " + std::to_string(P.health);
  s += ",\"max_health\": " + std::to_string(P.max_health);
  s += ",\"Str\": " + std::to_string(P.skills[0]) + ",\"End\": " + std::to_string(P.skills[1]);
  s += ",\"Spd\": " + std::to_string(P.skills[2]) + ",\"Lck\": " + std::to_string(P.skills[3]);
  s += ",\"Inventory\": {";
  for(int i = 0; i < P.inventory.size(); i++){
    if(i)
      s += ",";
    s += "\"item\": { \"name\":\"" + P.inventory[i].get_name() + "\",\"type\": \"" + P.inventory[i].get_type() + "\",\"stat\": " + std::to_string(P.inventory[i].get_stat()) + " }";
  }
  s += "},\"level\": " + std::to_string(P.level);
  s += ",\"experience\": " + std::to_string(P.experience);
  s += ",\"next_level\": " + std::to_string(P.next_level);
  s += ",\"weapon\": { \"name\":\"" + P.weapon.get_name() + "\",\"type\": \"" + P.weapon.get_type() + "\",\"stat\": " + std::to_string(P.weapon.get_stat()) + " }";
  s += ",\"armor\": " + P.armor.get_name() + "_" + P.armor.get_type() + "_" + std::to_string(P.armor.get_stat());
  s += " }";
  return nlohmann::json::parse(s);

}
