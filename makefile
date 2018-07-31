CC = g++
FILES = main.cpp error.cpp screen.cpp classes/dungeon.cpp classes/json_conversion.cpp classes/game.cpp classes/player.cpp classes/character.cpp classes/location.cpp classes/enemy.cpp functions.cpp  classes/item.cpp
OUT_EXE = project

build: $(FILES)
		$(CC) -lncurses -o $(OUT_EXE) $(FILES) -std=c++11
