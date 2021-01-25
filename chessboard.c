#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

//empty square = 0; pawns = p; knight = n; bishop = b; rook = r; queen = q; king = k
//uppercase means white piece and lowercase means black piece (ex: r = black rook and R = white rook)

int turn_number = 0; //if turn number even, white to move

char **setup_board() {
    char **chessboard = malloc(8*sizeof(char*)); //creating an array to store each row
    int row = 0;
    int column;
    for (row; row < 8; row++) { //putting an array of eight "squares" in each row
        chessboard[row] = malloc(8*sizeof(char));
    }
    row = 0;
    for (row; row < 8; row++) { //placing the pieces into each row
        int column = 0;
        if (row == 1) { // this is the row of white pawns
            for (column; column < 8; column++) {
                chessboard[row][column] =  'P';
            }
        }
        else {     
            if (row == 6) { // this is the row of black pawns
                for (column; column < 8; column++) {
                    chessboard[row][column] =  'p';
                }
            }
            else {
                if (row == 0) { // this is the row of other white pieces
                    chessboard[row][0] =  'R';
                    chessboard[row][1] =  'N';
                    chessboard[row][2] =  'B';
                    chessboard[row][3] =  'K';
                    chessboard[row][4] =  'Q';
                    chessboard[row][5] =  'B';
                    chessboard[row][6] =  'N';
                    chessboard[row][7] =  'R';
                }
                else {
                    if (row == 7) { // this is the row of other black pieces
                        chessboard[row][0] =  'r';
                        chessboard[row][1] =  'n';
                        chessboard[row][2] =  'b';
                        chessboard[row][3] =  'k';
                        chessboard[row][4] =  'q';
                        chessboard[row][5] =  'b';
                        chessboard[row][6] =  'n';
                        chessboard[row][7] =  'r';
                    }
                    else {
                        for (column; column < 8; column++) {
                            chessboard[row][column] =  0;
                        }
                    }
                }
            }
        }
    }
    return chessboard;
}

wchar_t piece_translate(char piece) { //returns the unicode chess piece
    wchar_t w_king = 0x2654;
    wchar_t w_queen = 0x2655;
    wchar_t w_rook = 0x2656;
    wchar_t w_bishop = 0x2657;
    wchar_t w_knight = 0x2658;
    wchar_t w_pawn = 0x2659;
    wchar_t b_king = 0x265A;
    wchar_t b_queen = 0x265B;
    wchar_t b_rook = 0x265C;
    wchar_t b_bishop = 0x265D;
    wchar_t b_knight = 0x265E;
    wchar_t b_pawn = 0x265F;
    if (piece == 'P'){
        return w_pawn;
    }
    if (piece == 'N'){
        return w_knight;
    }
    if (piece == 'B') {
        return w_bishop;
    }
    if (piece == 'R') {
        return w_rook;
    }   
    if (piece == 'Q') {
        return w_queen;
    }
    if (piece == 'K') {
        return w_king;
    }
    if (piece == 'p') {
        return b_pawn;
    }
    if (piece == 'n') {
        return b_knight;
    }
    if (piece == 'b') {
        return b_bishop;
    }
    if (piece == 'r') {
        return b_rook;
    }
    if (piece == 'q') {
        return b_queen;
    }
    if (piece == 'k') {
        return b_king;
    }
}

void print_board(char **chessboard) {
    setlocale(LC_CTYPE, ""); //this is so printing chess pieces works
    wprintf(L"-----------------------------------------\n");
    int row = 0;
    for (row; row < 8; row++) { 
        int column = 0;
        for (column; column < 8; column++) {
            if (chessboard[row][column] > 0){
                wprintf(L"| %lc  ", piece_translate(chessboard[row][column])); //wprintf has to be used from now on with the L infront of " text "
            }
            else {
                wprintf(L"|    ");
            }
            int i = 0;
        }
        wprintf(L"| \n");
        wprintf(L"-----------------------------------------");
        wprintf(L"\n");
    }
}

int *move_parse(char *move) { //turns a move like e2e4 into an array of four numbers (row, column, row, column)
    int *move_array = malloc(4 * sizeof(int));
    move_array[0] = move[0] - 97;
    move_array[1] = move[1] - 49;
    move_array[2] = move[2] - 97;
    move_array[3] = move[3] - 49;
    return move_array;
}

int piece_color(char piece) { //returns 0 if square is empty, 1 if white, 2 if black
    if ((piece > 96) && (piece < 123)) { // in the range of lowercase letters
        return 2;
    } 
    else {
        if ((piece > 64) && (piece < 91)) { // in the range of uppercase letters
            return 1;
        }
        else {
            return 0; //empty square
        }
    }
}

int add_move(char **chessboard, int r, int c, int rook_color, int *tp, int **move_list) {
    if (piece_color(chessboard[r][c]) == 0) {
        int *temp_arr = malloc(2*sizeof(int));
        temp_arr[0] = r;
        temp_arr[1] = c;
        move_list[*(tp)] = temp_arr;
        (*tp)++;
        return 0;
    }
    else {
        if (piece_color(chessboard[r][c]) != rook_color) {
            int *temp_arr = malloc(2*sizeof(int));
            temp_arr[0] = r;
            temp_arr[1] = c;
            move_list[*(tp)] = temp_arr;
            (*tp)++;
            return 1;
        }
        else {
            return 1;
        }
    }
}

int **rook_moves(char **chessboard, int row, int column) { //returns a 2-D int array of where the rook can move
    int r = row;
    int c = column;
    int rook_color = piece_color(chessboard[row][column]);
    int **move_list = malloc(8 * sizeof(int*));
    int t = 0; //counter variable for the temporary array
    int *tp = &t;
    //looks to the ascending rows
    r++;
    for (r; r < 8; r++) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
    }
    r = row;
    //looks to the descending rows
    r--;
    for (r; r > 0; r--) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
    }
    r= row;
    //looks to the ascending columns
    c++;
    for (c; c < 8; c++) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
    }
    c = column;
    //looks to the descending columns
    c--;
    for (c; c > 0; c--) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **knight_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int rook_color = piece_color(chessboard[row][column]);
    int **move_list = malloc(8 * sizeof(int*));
    int t = 0; 
    int *tp = &t;
    
    if ((r + 2 < 8) && (c + 1 < 8)) {
        add_move(chessboard, r + 2, c + 1, rook_color, tp, move_list);
    }
    if ((r + 1 < 8) && (c + 2 < 8 )) {
        add_move(chessboard, r + 1, c + 2, rook_color, tp, move_list);
    }
    if ((r + 2 < 8) && (c - 1 > 0)) {
        add_move(chessboard, r + 2, c - 1, rook_color, tp, move_list);
    }
    if ((r + 1 < 8) && (c - 2 > 0)) {
        add_move(chessboard, r + 1, c - 2, rook_color, tp, move_list);
    }
    if ((r - 2 > 0) && (c - 1 > 0)) {
        add_move(chessboard, r - 2, c - 1, rook_color, tp, move_list);
    }
    if ((r - 1 > 0) && (c - 2 > 0)) {
        add_move(chessboard, r - 1, c - 2, rook_color, tp, move_list);
    }
    if ((r - 2 > 0) && (c + 1 < 8)) {
        add_move(chessboard, r - 2, c + 1, rook_color, tp, move_list);
    }
    if ((r - 1 > 0) && (c + 2 < 8)) {
        add_move(chessboard, r - 1, c + 2, rook_color, tp, move_list);
    }
    move_list[t + 1] = 0;
    return move_list;
}

int **bishop_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int rook_color = piece_color(chessboard[row][column]);
    int **move_list = malloc(8 * sizeof(int*));
    int t = 0; 
    int *tp = &t;
    r++;
    c++;
    while((r < 8) && (c < 8)) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
        r++;
        c++;
    }
    r = row;
    c = column;
    r++;
    c--;
    while((r < 8) && (c > 0)) {  
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
        r++;
        c--;
    }
    r = row;
    c = column;
    r--;
    c++;
    while((r > 0) && (c < 8)) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
        r--;
        c++;
    }
    r = row;
    c = column;
    r--;
    c--;
    while((c > 0) && (c > 0)) {
        if (add_move(chessboard, r, c, rook_color, tp, move_list)) {
            break;
        }
        r--;
        c--;
    }
    move_list[t + 1] = 0;
    return move_list;
}

int pos_moves(int **move_list) {
    setlocale(LC_CTYPE, "");
    int i = 0;
    while(move_list[i]) {
        wprintf(L"coords: %d, %d\n", move_list[i][0], move_list[i][1]);
        i++;
    }
}
int **king_moves(char **chessboard, int row, int column) {
    int r = row;
    int c = column;
    int rook_color = piece_color(chessboard[row][column]);
    int **move_list = malloc(8 * sizeof(int*));
    int t = 0; 
    int *tp = &t;
    
    if ((r + 2 < 8) && (c + 1 < 8)) {
        add_move(chessboard, r + 2, c + 1, rook_color, tp, move_list);
    }
}
int move_valid(int *parsed_moves) {
    
}

int main() {
    char ** chessboard = setup_board();
    chessboard[4][5] = 'n';
    int **b = knight_moves(chessboard, 4, 5);
    
    
    pos_moves(b);
    
    print_board(chessboard);   

    return 0; 
}

/*
checklist:
1. piece logic
2. game over (king is eaten)
-comparison function
3. who's turn it is
4. convert to 64-size array
5. display as black/white
6. add letters/numbers to board
*/
