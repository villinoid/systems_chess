# DEVLOG

- 1/12 - Francesco Vlad and Yulin - Worked on Initial Proposal
- 1/18 - Vlad and Yulin - Added server framework - Similar to HW 17 - Server communicates with 1 client - Adapted to work with 2 clients.
- 1/22 - Francesco - Set server up to read and write to both clients sequentially - Server reads from client 1, writes bac, reads from client 2, writes back, on a loop.
- 1/23 - Francesco - Started framework for inter client communication on server side (Explicit Handshake call and then read/write code) - Added player selection code (When client runs, it ask whether it should start as player 1 or player 2)
- 1/24 - Vlad - Finished communication between 2 clients via server (Server handshakes, reads from client 1, writes to client 2, reads from 2, and writes to 1, on a loop)
- 1/24 - Yulin - Created chessboard and rook moves - Created 2D array to store chess pieces, methods to translate to and from chessboard and a board state string, and established momement checks for the rook.
- 1/25 - Yulin - Finished chessboard and move list for all pieces - Finished moment checks for all pieces - Eating a piece also completed
- 1/25 - Vlad - Fixed malloc issues, various bugs, made visual improvements
- 1/25 - Yulin - Added flipped print so board is "right way" - Otherwise one player is playing on bottom of board and one on top.
- 1/25 - Francesco - Added save game functionality - Player 1 can "save" instead of play a move and save the game state to a file. This game state can then be reopened at the start of a Player 1 session.
- 1/25 - Francesco - Added win condition/game end (If either king is eaten game ends - Winner announced) - Fixed white bishops causing segfaults (Typo in Bishop movement function)
- 1/25 - Francesco - Finished README and DEVLOG
