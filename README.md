## Two Player Chess Client
By Francesco Siniscalco, Vladislav Vostrikov and Yulin Zheng

The goal is to create a chess interface where two players on separate clients can play against each other - (Using a server - and likely implementing a spectator client).

The terminal will print out the board and piece positions (unicode chess pieces; letters can be used for terminals that have display issues) line by line. The player can input a move like “e2e4” and this move will be relayed to the other player. After the game is over, a game file can be exported to be viewed later.

### Topics:
- Use a server and client with pipes to transmit moves (timers can also be added) - while having the server also update a game state file.
    - Using a timer might deal with shared memory, but we will finalize this after we learn about it in class
    - If taught in class - Have server/clients work across network would be very nice - Not having to play on same computer
- Send signals from the different processes (ex: opponent has resigned, show menu for exporting game / resetting the board / pausing game)
- Exporting games to a file and reading game files
- Allocating memory to store the matrix of piece locations

### Responsibilities:
- Francesco: implementing the rules of chess and algorithms to detect if valid moves are made
- Vlad: reading input from user and translating that into chess moves / reading and writing those moves into files
- Yulin: creating the communications system for clients to interact and the synchronized moves and time between players

### Algorithms/Data Structures:
- Structs for squares on the board (ex: occupied/not occupied) and for pieces and what moves they are allowed to make
- Structs? or strings, to transfer info across pipes regarding game state and moves.
- Algorithms to determine what moves are legal
    - Detects if a piece on that square can move to the desired square - and eat
    - Detects if the king is in check/checkmate
- Variable to keep count of score - Each piece eaten has score value

### Expected Completion Dates:
- No project due date so unsure - Time estimates instead with approximate order of completion:
    - Have working server/client communication with ability to send moves (1st day of work)
    - Have console print out board and read in moves (1st day of work)
    - Algorithm for movement and check/checkmate/eating pieces (2nd-3rd day of work)
    - Establishing save game/menu and signals for pausing/other inputs (4th day of work)
    - Having move timer (5th day of work)
    - If taught in class - Have server/clients work across network (1 - a few days of work?)
    - Score system based on pieces eaten and time taken (7th day of work - 1 day total)
