# Unseen_Journey_Quest
## Game OverView:
A maze game developed using data structures such as lists,stacks and queues. The objective of the game is to find the key within a maze (size is determined by the user) and navigate to the door to win the game. Key and door are hidden and the player locates these items through a hint based system,prompting the user whether they are moving away or closer to the item.
Player can move in up,down,left and right using the arrow keys directions, with the following constraint that they cannot immeadiately move back to their previous position unless using their limited undo movements (by pressing space bar).
There are coins generated randomly after every 15s and acquiring coins increases no of undos player can perform while also incrementing score. Bombs are also randomly placed and landing on any one renders results in game over. Player has limited no of moves which are calculated using manhattan city block distance between the player,key and door and if the player runs out of moves before reaching the door with the key, the player loses. Total score is calculated by adding remaining no of moves and no of coins collected.
At the end of the game, coordinates of coins that were picked by the player are revealed in the order they were picked and the positions of the key and door are also revealed.

## Game Features:
  1. Player Movement(UP,DOWN,LEFT,RIGTH keys)
  2. Random coins Regeneration
  3. Random Bomb placement
  4. Hint system(based on Manhattan city block distance)
  5. Random Key and Door placement
  6. Player Undo functionality(using space bar)
## Rules:
1. Player can move up, down,left right.
2. Player cannot move to its previous location without using undo move.
3. Collecting coins increases undo moves and score.
4. Player has limited no of moves determined by distance from key and distance from key and door(using manhattan distance).
5. Hint gives player information whether they are moving away or closer to key/door.
6. Once moves are zero and player has not reached door with key, player has lost.
7. Stepping on a bomb will result in game over.
8. Object representation:
   >Player=Red "P"
   >Coins=Yellow "C"
   >Bombs=Green "B"
   >Key=Green "K"(revealed at game over)
   >Door=Green "D"(Revealed at game over)
9. Score is calculated from No of coins collected and remaining moves available(IF any)
## Library Installation(For users Running VS Community):
  This project utilizes the use of pdcurses to display the game on terminal. To setup pdcurses on windows,
  follow these instructions:
  1. Download pdcurses from its github page or by pressing this 
     link:https://github.com/wmcbrine/PDCurses/archive/refs/tags/3.9.zip
  2. Create a new folder and extract the installed library folder.
  3. Download CMake GUI(Make sure to provide the given CMakeLists.txt file inside the folder you have extracted).
  4. Once CMake has been downloaded, open the app and in browse source, choose the extracted folder.
  5. In where to build, choose the created folder to build your binaries.
  6. You will be prompted to choose your environment and system archirtecture(choose your current version of VS Community         and your system architecture type)
  7. Click on configure and then generate.
  8. Head over to the folder and locate the .sln file that has been created.Once located open and build the project(ignore       all warnings) 
  9. Open the game project in VS community.
  10. In project properties, head over to C/C++.
  11. In additional libraries dependencies, include the path to PDCurses-3.9(the location which contains the header file     
      curses.h)
  12. In general linker settings, add the path to the Debug folder in your main folder.
  13. In linker input settings, add "pdcurses.lib".Click ok and build the project.
## Game Visuals
### Game Menu:
<img width="514" alt="image" src="https://github.com/user-attachments/assets/678c4bf8-331c-4562-8180-2fcde31fd117">

### Initial Game state:
<img width="413" alt="image" src="https://github.com/user-attachments/assets/f1bc2509-03f8-4931-9afe-04ac61328aee">

### Final Game State:
Revealing key and door positions along with coins collected in order first to last:
<img width="428" alt="image" src="https://github.com/user-attachments/assets/5c84cd4b-9e50-4f66-94c8-07a86a72fac8">
