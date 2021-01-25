## Two Player Chess Client
By Francesco Siniscalco, Vladislav Vostrikov and Yulin Zheng - Period 10

Our project is a two-player chess game connected by a server. The board is printed in unicode, and the server manages the turn based gameplay. The game checks whether moves are valid, and has a save game state feature.

### Libraries
No external installations are required and everything can be compiled using gcc.
Here are the list of libaries we used:

- #include <stdio.h>
- #include <stdlib.h>
- #include <string.h>
- #include <sys/types.h>
- #include <sys/stat.h>
- #include <unistd.h>
- #include <fcntl.h>
- #include <signal.h>
- #include <wchar.h>
- #include <locale.h>

### What Aspects of Systems Programming We Used
- Pipes (Communicating Between Server and Client)
- Allocating Memory (Storing Chessboard Info)
- Working with Files (Save Game Functionality)
- Signals (Checking Client State)

### Instructions
- To start compile using make, and start the server with "./server".
- Start 2 clients using "./client" and when prompted make one player 1 and the other 2.
    - You can then decide to load a saved game or start a new one (more info below)
    - Please complete all player 1 processes before initializing player 2 (that is, enter "1" when prompted and y/n for saved game before entering "2" for player 2)
- At this point it is player 1's turn, enter a move. You start by writing the coordinates of the piece you want to move, letter first then number, and then by writing the coordinates of the place you want to move the piece to (An example move is e2e4. Don't worry, "wrong" moves won't be allowed by the program.)
- After a move is entered, the other player will be prompted for a move and so the game begins!
- When a king is eaten by another piece, the game will end, and you will be greeted by a victory message.
- To save the game, type "save" as player 1, and when prompted, choose a name for the save file.
    - When a game is saved, the client will auto-disconnect
    - You can load this game in later when re-connecting the client and typing in the name 
- To exit, both players and server need to "Ctrl+C" - Otherwise the server will attempt a reconnection.

### Notes
- The terminal being used has to support unicode output
- Please use a terminal with a white background 
    - If a dark background is used, the pieces will have inverted colors

### Bugs/Limitations
- When attempting a reconnection, the disconnected user's turn will be skipped.
- Not all chess rules implemented - Castling and Pawn promoting when reaching the opponent's edge of the board was not implemented.
