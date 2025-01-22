#ifndef __PIECES_H__
#define __PIECES_H__

#include "common.h"

#define MAX_NUM_PIECES 7
#define PIECE_SIZE 4


typedef struct{
	char name;
	char board [PIECE_SIZE][PIECE_SIZE];
	int rows;
	int cols;
} Piece;

// Lab 1 - initialize, print, rotate and make pieces
void init_piece(Piece *p);
void print_piece(Piece p);
void rotate_clockwise(Piece *p);
void rotate_counter_clockwise(Piece *p);

Piece make_O(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'O'; piece.rows = 2; piece.cols = 2;
	piece.board[0][0] = '#'; piece.board[0][1] = '#'; 
	piece.board[1][0] = '#'; piece.board[1][1] = '#';
	return piece;
};
Piece make_I(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'I'; piece.rows = 3; piece.cols = 1;
	piece.board[0][0] = '#'; 
	piece.board[0][1] = '#'; 
	piece.board[0][2] = '#';
	return piece;
};
Piece make_S(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'S'; piece.rows = 2; piece.cols = 3;
	piece.board[0][1] = '#'; 
	piece.board[0][2] = '#'; 
	piece.board[1][0] = '#';
	piece.board[1][1] = '#';
	return piece;
};
Piece make_Z(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'Z'; piece.rows = 2; piece.cols = 3;
	piece.board[0][0] = '#'; 
	piece.board[0][1] = '#'; 
	piece.board[1][1] = '#';
	piece.board[1][2] = '#';
	return piece;
};
Piece make_L(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'L'; piece.rows = 3; piece.cols = 2;
	piece.board[0][0] = '#'; 
	piece.board[1][0] = '#';
	piece.board[2][0] = '#';
	piece.board[2][1] = '#';
	return piece;
};
Piece make_J(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'J'; piece.rows = 3; piece.cols = 2;
	piece.board[0][1] = '#'; 
	piece.board[1][1] = '#'; 
	piece.board[2][0] = '#';
	piece.board[2][1] = '#';
	return piece;
};
Piece make_T(){
	Piece piece;
	init_piece(&piece);
	piece.name = 'T'; piece.rows = 2; piece.cols = 3;
	piece.board[0][0] = '#'; 
	piece.board[0][1] = '#'; 
	piece.board[0][2] = '#';
	piece.board[1][1] = '#';
	return piece;
};

#endif
