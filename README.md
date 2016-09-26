# Reversi
Battle Of Bots #5 - Hackerearth

Battle of Bots is an Artificial Intelligence competition that runs for 6 Days. The objective is to create a bot for a two player game that will compete against other bots.


**Rules**

The game for this challenge was Reversi(Othello). It is played on an 10X10 board. The game starts with two black and two white pieces set up like the figure below

![alt tag](http://www.britishothello.org.uk/stboard.gif)

Black always plays first with players then taking alternate turns.

A player must place a stone on the board, in such a position that there exists at least one straight (horizontal, vertical, or diagonal) occupied line between the new stone and another stone of same color, with one or more contiguous other color stone between them.


At each turn a player must place a disc with their colour face up on one of the empty squares of the board, adjacent to an opponent's disc such that one or more straight lines (horizontal, vertical or diagonal) are formed from the newly placed disc, through one or more of the opponent's discs and up to other discs of their own colour already on the board. All the intervening discs of the opponent's colour are flipped to the colour of the newly laid disc.
Discs may be flipped from one colour to the other but once played are not moved from one square to another or removed from the board.
Players may not pass unless there is no valid move available to them in which case they must pass.
Play continues until neither player is able to move or when all 64 squares have been filled.


**Running the Bot**

To run the bot, run bot.cpp and input an 10*10 grid filled with 0's, 1's, 2's and 3's. followed by a number either 1 or 2 to indicate which players turn it is. 

Note:
- 0's - Empty space no move available
- 1's - Player 1
- 2's - Player 2      
- 3's - Possible move available


**Results**

My Bot placed 47th in the competition.
