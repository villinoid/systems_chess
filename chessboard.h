#ifndef CHESSBOARD
#define CHESSBOARD

char **setup_board();
wchar_t piece_translate(char);
void print_board(char **);
int *move_parse(char *);
int piece_color(char);
int add_move(char **, int, int, int, int *, int **)
#endif