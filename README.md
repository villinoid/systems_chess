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

### Instructions
- To start compile using make, and start the server with "./server".
- Start 2 clients using "./client" and when prompted make one player 1 and the other 2.
- You can then decide to load a saved game or start a new one
- At this point it is player 1's turn, enter a move such as e2e4.
- After a move is entered, it is the other player's turn, and so the game begins!
- To save the game, type "save" as player 1, and when prompted choose a name for the save file.
- To exit, both players and server need to "Ctrl+C" - Otherwise the server will attempt a reconnection.


### Bugs
- When attempting a reconnection, the disconnected user's turn will be skipped.
