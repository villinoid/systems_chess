#ifndef CHESSBOARD
#define CHESSBOARD

char **setup_board();
wchar_t piece_translate(char);
void print_board(char **);
int *move_parse(char *);
int piece_color(char);
int add_move(char **, int, int, int, int *, int **);
void read_board(char **, char *);
void write_board(char **, char *);
int **rook_moves(char **chessboard, int row, int column);
int **knight_moves(char **chessboard, int row, int column);
int **bishop_moves(char **chessboard, int row, int column);
int **king_moves(char **chessboard, int row, int column);
int **queen_moves(char **chessboard, int row, int column);
void pawn_add_move(char **chessboard, int r, int c, int *tp, int **move_list);
int **pawn_moves(char **chessboard, int row, int column);
int pos_moves(int **move_list);
int **on_square(char **chessboard, int r, int c);
int in_move_list(int **move_list, int r, int c);
int move_valid(char **chessboard, int *parsed_moves);
#endif