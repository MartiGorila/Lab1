#include "pieces.h"

void init_piece(Piece *p){
	p->rows = 0; p->cols = 0;
    for(int i=0; i<PIECE_SIZE; i++){
        for(int j=0; j<PIECE_SIZE; j++){
            p->board[i][j] = '.';

        }
    }
}

void print_piece(Piece p){
    printf("Name: %c; Size: %dx%d\n", p.name, p.rows, p.cols);
    for(int i=0; i<PIECE_SIZE; ++i){
        for(int j=0; j<PIECE_SIZE; ++j){
            printf("%c", p.board[i][j]);
        }
        printf("\n");
    }
}

void rotate_clockwise(Piece *p){
    Piece temporal;
    init_piece(&temporal);
    for(int c=0; c<PIECE_SIZE; c++){
        for(int r=0; r<PIECE_SIZE; r++){
            temporal.board[c][p->rows-1-r] = p->board[r][c];
        }
    }
    *p=temporal;
}

void rotate_counter_clockwise(Piece *p){
    Piece temporal;
    init_piece(&temporal);
    for(int c=0; c<PIECE_SIZE; c++){
        for(int r=0; r<PIECE_SIZE; r++){
            temporal.board[r][c] = p->board[p->rows-1-c][r];
        }
    }
    *p=temporal;
}

Piece make_O(){
    // ToDo in LAB 1
}

Piece make_I(){
    // ToDo in LAB 1
}


Piece make_S(){
	// ToDo in LAB 1
}


Piece make_Z(){
    // ToDo in LAB 1
}

Piece make_L(){
    // ToDo in LAB 1
}

Piece make_J(){
    // ToDo in LAB 1
}

Piece make_T(){
    // ToDo in LAB 1
}

