#ifndef PIECES
#define PIECES
int **rook_moves(char **chessboard, int row, int column);
int **knight_moves(char **chessboard, int row, int column);
int **bishop_moves(char **chessboard, int row, int column);
int **king_moves(char **chessboard, int row, int column);
int **queen_moves(char **chessboard, int row, int column);
void pawn_add_move(char **chessboard, int r, int c, int *tp, int **move_list);
int **pawn_moves(char **chessboard, int row, int column);
#endif