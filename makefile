CC = g++
FILES = test.cpp classes/character.cpp classes/location.cpp classes/enemy.cpp functions.cpp  classes/item.cpp
OUT_EXE = project
#serparate files in FILES by spaces
build: $(FILES)
		$(CC) -o $(OUT_EXE) $(FILES)
