# Unseen_Journey_Quest
Game OverView:
A maze game developed using data structures such as lists,stacks and queues. The objective of the game is to find the key within a maze (size is determined by the user) and navigate to the door to win the game. Key and door are hidden and the player locates these items through a hint based system,prompting the user whether they are moving away or closer to the item.
Player can move in up,down,left and right using the arrow keys directions, with the following constraint that they cannot immeadiately move back to their previous position unless using their limited undo movements (by pressing space bar).
There are coins generated randomly after every 15s and acquiring coins increases no of undos player can perform while also incrementing score. Bombs are also randomly placed and landing on any one renders results in game over. Player has limited no of moves which are calculated using manhattan city block distance between the player,key and door and if the player runs out of moves before reaching the door with the key, the player loses. Total score is calculated by adding remaining no of moves and no of coins collected.
At the end of the game, coordinates of coins that were picked by the player are revealed in the order they were picked and the positions of the key and door are also revealed.
