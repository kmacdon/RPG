#include <nlohmann/json.hpp>

class Item;
class Location;
class Player;
class Dungeon;

using nlohmann::json;

void to_json(nlohmann::json& j, const Item& I);
void from_json(const nlohmann::json& j, Item& I);

void to_json(nlohmann::json& j, const Location& L);
void from_json(const nlohmann::json& j, Location& L);

void to_json(nlohmann::json& j, const Player& P);
void from_json(const nlohmann::json& j, Player& P);

void to_json(nlohmann::json& j, const Dungeon& D);
void from_json(const nlohmann::json& j, Dungeon& D);
