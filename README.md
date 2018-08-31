Implementing an RPG in C++ using a Text-Based User Interface
================

### Introduction

I began this project over the summer having been inspired by another C++ RPG game I made for a class project in the Fall. That game, which I worked on with a partner, involved moving an '0' character around a 20 x 10 map using the WASD keys to collect $ symbols. The goal was to collect 10 $ and enemies would be randomly generated from among a few types to challange the player with math questions. If the player answered incorrectly, they lost a health point of which they only had 3.

This was a very simple project requiring only a couple hundred lines of code, but it was my first exposure to changing input and output to the terminal by getting commands directly after key presses or creating constantly updating output. For this program, I decided to go deeper and create a more complicated game screen using the ncurses library to display different information screens on the terminal and allow the player to use arrow keys to make selections. I also utilized classes and inheritance more, helping to break the game up into manageable and logical pieces.

### Overview

![Welcome Screen](images/welcome_screen.png)

This is the welcome screen that appears when loading the game. It provides a basic description of the game and allows the player to choose between starting a new game or reloading a previous save.

![Main Screen](images/main_screen.png)

This is the main game screen. The player can enter commands on the left and typing 'help' will bring up a list of possible options. On the right the player's stats are displayed along with a map screen showing possible locations to move to. The POI are dungeons that can be explored, offering enemies to battle and items to collect. There is also a chance of having a random encounter with an enemy when moving between locations.

![Inventory Screen](images/inventory_screen.png)

By entering 'inventory' the player can open up the inventory screen to use or equip items. Pressing 'q' will exit the inventory screen.

![Battle Screen](images/battle_screen.png)

The battle screen is implemented similar to the inventory screen, allowing the player to use the arrow keys to select options. Defeated enemies have a chance of dropping items which will automatically be added to the player's inventory.

### External Libraries

I was having difficulty creating a save system originally since I was writing code to store objects as characters. I began by trying to write functions converting all the information to a single string which was time consuming, and I found that my attempt to compress the information was essentially a JSON implementation. I decided just to find a json library for c++ which I did with nlohmann/json.hpp. It was easy to set up and saved me a lot of time and hassle with file management. This also enabled me to quickly edit or add things like locations and player data since I only had to modify text files rather than the code itself.

The other new external library I used was ncurses for the graphics. I had planned on just using a set of functions I created for my class project to get raw input from the terminal, but while I was searching for a way to bold terminal output I found ncurses. It took a little bit of trial and error and a good amount of googling but I managed to get it working and it made the user interface much cleaner and simpler. It also allowed me to implement things like the stats and map screens.

The game itself is divided into 7 classes: game, character, enemy, player(this and enemy inherit from character), item, location, and dungeon. The classes are self explanatory with game handling all the loading and storing of game data, creating output, and running the game itself.

### Lessons Learned

When I first began this project, I made sure to plan out as much as I could before writing any code. I created flowcharts for the main functions that would be used and wrote out each class with its members and functions, refining each multiple times as I noticed potential problems or decided to add features. Creating the earliest version of this game was certainly much easier because I had resolved many problems that otherwise would have required rewriting large amounts of code.

However as I developed the game I decided to add more features such as using ncurses and creating a save system among others. These newer features were not as planned out as the initial stages, and although they certainly benefited the game, I began to run into many more problems as the game sprawled, making troubleshooting much more difficult. If I had taken the same planning approach midway through development that I did in the beginning, I am sure things would have been simpler and for future projects, I plan on researching much more in the beginning so that I am not completely overhauling my UI in the middle of the project.

The code could also have been made easier to read and maintain if I had created more functions to split up the code. Even some functions that had seemed simple in a flowchart required much more code than I anticapated, especially as the scope of the game grew. I eventually implemented a log system detailing when functions were entered and exited which helped trackdown errors more quickly.

### Moving Forward

There are many features I would like to add to the game given the time. Adding shops to purchase or sell items would benefit the game by providing the player with more interactions. Creating NPCs and a dialogue system would also greatly improve the game if properly planned and implemented. Overall, creating this game helped me improve my C++ programming skills greatly by introducing me to new libraries and providing experience working with object-oriented programming. I have only taken a few classes using C++, so I enjoyed the opportunity to learn more about the language on my own.
