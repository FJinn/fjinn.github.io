# -> [Tic Tac Toe With Photon](/Assignments/DataNetworking/Multiplayer_TicTacToe/TicTacToe.cpp) <-

<img src="https://github.com/FJinn/fjinn.github.io/blob/master/Assignments/DataNetworking/Image/TicTacToe.gif?raw=true"/>

A simple Tic Tac Toe game is made with the intention for me to practice and learn about networking in game.

In this Tic Tac Toe game, Photon library is used to communicate data among different machine.

As a constraint, the data that is used to communicate between two players is limited to the size of 1 byte (8 bits).

I used 4 bits to store the information about the game board and 1 bit for the game state (restart, start, undo).

When packaging the data to send over to another player, the game board information such as occupied cell, will be set into an unsigned 8 bits char.

Then the data will be shifted to left with 1 bit to make space for storing the game state, which is indicated with number.

The unsigned 8 bits char will then be sent to another player.

The received unsigned 8 bits char will be unpacked in a reverse order to get the correct information from the other player.
