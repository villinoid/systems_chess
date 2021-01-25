#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chessboard.h"
int **rook_moves(char **chessboard, int row, int column) { //returns a 2-D int array of where the rook can move
    int r = row;
    int c = column;
    int color = piece_color(chessboard[row][column]);
    int **move_list = malloc(32 * sizeof(int*));
    int t = 0; //counter variable for the temporary array
    int *tp = &t;
    //looks to the ascending rows
    r++;
    for (r; r < 8; r++) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
    }
    r = row;
    //looks to the descending rows
    r--;
    for (r; r >= 0; r--) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
    }
    r= row;
    //looks to the ascending columns
    c++;
    for (c; c < 8; c++) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
    }
    c = column;
    //looks to the descending columns
    c--;
    for (c; c >= 0; c--) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **knight_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int color = piece_color(chessboard[row][column]);
    int **move_list = malloc(32 * sizeof(int*));
    int t = 0;
    int *tp = &t;

    if ((r + 2 < 8) && (c + 1 < 8)) {
        add_move(chessboard, r + 2, c + 1, color, tp, move_list);
    }
    if ((r + 1 < 8) && (c + 2 < 8 )) {
        add_move(chessboard, r + 1, c + 2, color, tp, move_list);
    }
    if ((r + 2 < 8) && (c - 1 >= 0)) {
        add_move(chessboard, r + 2, c - 1, color, tp, move_list);
    }
    if ((r + 1 < 8) && (c - 2 >= 0)) {
        add_move(chessboard, r + 1, c - 2, color, tp, move_list);
    }
    if ((r - 2 >= 0) && (c - 1 >= 0)) {
        add_move(chessboard, r - 2, c - 1, color, tp, move_list);
    }
    if ((r - 1 >= 0) && (c - 2 >= 0)) {
        add_move(chessboard, r - 1, c - 2, color, tp, move_list);
    }
    if ((r - 2 >= 0) && (c + 1 < 8)) {
        add_move(chessboard, r - 2, c + 1, color, tp, move_list);
    }
    if ((r - 1 >= 0) && (c + 2 < 8)) {
        add_move(chessboard, r - 1, c + 2, color, tp, move_list);
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **bishop_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int color = piece_color(chessboard[row][column]);
    int **move_list = malloc(32 * sizeof(int*));
    int t = 0;
    int *tp = &t;
    r++;
    c++;
    while((r < 8) && (c < 8)) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
        r++;
        c++;
    }
    r = row;
    c = column;
    r++;
    c--;
    while((r < 8) && (c >= 0)) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
        r++;
        c--;
    }
    r = row;
    c = column;
    r--;
    c++;
    while((r >= 0) && (c < 8)) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
        r--;
        c++;
    }
    r = row;
    c = column;
    r--;
    c--;
    while((r >= 0) && (c >= 0)) {
        if (add_move(chessboard, r, c, color, tp, move_list)) {
            break;
        }
        r--;
        c--;
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **king_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int color = piece_color(chessboard[row][column]);
    int **move_list = malloc(32 * sizeof(int*));
    int t = 0;
    int *tp = &t;
    if ((r + 1 < 8) && (c + 1 < 8)) {
        add_move(chessboard, r + 1, c + 1, color, tp, move_list);
    }
    if ((r + 1 < 8) && (c - 1 >= 0)) {
        add_move(chessboard, r + 1, c - 1, color, tp, move_list);
    }
    if ((r - 1 >= 0) && (c + 1 < 8)) {
        add_move(chessboard, r - 1, c + 1, color, tp, move_list);
    }
    if ((r - 1 >= 0) && (c - 1 >= 0)) {
        add_move(chessboard, r - 1, c - 1, color, tp, move_list);
    }
    if (r + 1 < 8) {
        add_move(chessboard, r + 1, c, color, tp, move_list);
    }
    if (r - 1 >= 0) {
        add_move(chessboard, r - 1, c, color, tp, move_list);
    }
    if (c + 1 < 8) {
        add_move(chessboard, r, c + 1, color, tp, move_list);
    }
    if (c - 1 >= 0) {
        add_move(chessboard, r, c - 1, color, tp, move_list);
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **queen_moves(char **chessboard, int row, int column) {
    int **move_list = malloc(32 * sizeof(int*));
    int **b = bishop_moves(chessboard, row, column);
    int **r = rook_moves(chessboard, row, column);
    int i = 0;
    int j = 0;
    while(b[i]) {
        move_list[j] = b[i];
        j++;
        i++;
    }
    int k = 0;
    while(r[k]) {
        move_list[j] = r[k];
        j++;
        k++;
    }
    move_list[j + 1] = 0;
    return move_list;
}

void pawn_add_move(char **chessboard, int r, int c, int *tp, int **move_list) {
    int *temp_arr = malloc(2*sizeof(int));
    temp_arr[0] = r;
    temp_arr[1] = c;
    move_list[*(tp)] = temp_arr;
    (*tp)++;
}

int **pawn_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int color = piece_color(chessboard[row][column]);
    int **move_list = malloc(32 * sizeof(int*));
    int t = 0;
    int *tp = &t;
    if (color == 1) {
        if ((r + 1 < 8) && (c + 1 < 8)) {
            int p = piece_color(chessboard[r + 1][c + 1]);
            if ((p != color) && (p != 0)) {
                pawn_add_move(chessboard, r + 1, c + 1, tp, move_list);
            }
        }
        if ((r + 1 < 8) && (c - 1 >= 0)) {
            int p = piece_color(chessboard[r + 1][c - 1]);
            if ((p != color) && (p != 0)) {
                pawn_add_move(chessboard, r + 1, c - 1, tp, move_list);
            }
        }
        if (r + 1 < 8) {
            int p = piece_color(chessboard[r + 1][c]);
            if (p == 0) {
                pawn_add_move(chessboard, r + 1, c, tp, move_list);
                if (row == 1) {
                    int p1 = piece_color(chessboard[r + 2][c]);
                    if (p1 == 0) {
                        pawn_add_move(chessboard, r + 2, c, tp, move_list);
                    }
                }
            }
        }
    }
    else {
        if ((r - 1 >= 0) && (c + 1 < 8)) {
            int p = piece_color(chessboard[r - 1][c + 1]);
            if ((p != color) && (p != 0)) {
                pawn_add_move(chessboard, r - 1, c + 1, tp, move_list);
            }
        }
        if ((r - 1 >= 0) && (c - 1 >= 0)) {
            int p = piece_color(chessboard[r - 1][c - 1]);
            if ((p != color) && (p != 0)) {
                pawn_add_move(chessboard, r - 1, c - 1, tp, move_list);
            }
        }
        if (r - 1 >= 0) {
            int p = piece_color(chessboard[r - 1][c]);
            if (p == 0) {
                pawn_add_move(chessboard, r - 1, c, tp, move_list);
                if (row == 6) {
                    int p1 = piece_color(chessboard[r - 2][c]);
                    if (p1 == 0) {
                        pawn_add_move(chessboard, r - 2, c, tp, move_list);
                    }
                }
            }
        }
    }
    move_list[t + 1] = 0;
    return move_list;
}
