#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
//empty square = 0; pawns = p; knight = n; bishop = b; rook = r; queen = q; king = k
//uppercase means white piece and lowercase means black piece (ex: r = black rook and R = white rook)

int turn_number = 0; //if turn number even, white to move

char **setup_board() {
    
    char **chessboard = malloc(64 * sizeof(char)); //creating an array to store each row

    int row = 0;
    for (row; row < 8; row++) { //putting an array of eight "squares" in each row
        chessboard[row] = malloc(8 * sizeof(char));
    }

    row = 0;
    for (row; row < 8; row++) { //placing the pieces into each row
        
        //printf("row: %d\n", row);
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

void analyze() {

}

wchar_t piece_translate(char piece) {
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
    int row = 0;
    for (row; row < 8; row++) { 
        int column = 0;
        for (column; column < 8; column++) {
            if (chessboard[row][column] > 0){
                wprintf(L"| %lc ", piece_translate(chessboard[row][column]));
                //wchar_t b_knight = 0x265E;
                
            }
            else {
                wprintf(L"|   ");
            }
            int i = 0;
        }
        wprintf(L"| \n");
        wprintf(L"---------------------------------");
        wprintf(L"\n");
    }
}

int main() {
    
    char ** chessboard = setup_board();
    print_board(chessboard);
    return 0; 
}