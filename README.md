## Two Player Chess Client
By Francesco Siniscalco, Vladislav Vostrikov and Yulin Zheng - Period 10

Our project is a 2 player and 1 server chess game. The board is printed in unicode, and the server manages the turn based gameplay. The game checks whether moves are valid, and has a save game state function.

### Notes
- Terminal used has to support unicode
- White terminal is best - otherwise pieces will have inverted colors

### Libraries
There are no unusual required Libraries

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
- Pipes (Named and Unnamed)
- Allocating Memory (Storing Chessboard Info)
- Working with Files (Save Game Functionality)
- Signals (Checking Client State)
- Processes (Server, Client1, Client2)

### Instructions
- To start compile using make, and start the server with "./server".
- Start 2 clients using "./client" and when prompted make one player 1 and the other 2.
- You can then decide to load a saved game or start a new one
- At this point it is player 1's turn, enter a move. You start by writing the coordinates of the piece you want to move, letter first then number, and then by writing the coordinates of the place you want to move the piece to (An example move is e2e4. - Don't Worry, "wrong" moves won't be allowed by the program.
- After a move is entered, it is the other player's turn, and so the game begins!
- When a king is eaten by another piece, the game will end, and you will be greeted by a victory message.
- To save the game, type "save" as player 1, and when prompted choose a name for the save file.
- To exit, both players and server need to "Ctrl+C" - Otherwise the server will attempt a reconnection.


### Bugs/Limitations
- When attempting a reconnection, the disconnected user's turn will be skipped.
- Not all chess rules implemented - Castling and Pawn changing when touching the opponents edge of the board not implemented.
