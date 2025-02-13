#include "pieces.h"

void init_piece(Piece *p) {
  p->rows = 0;
  p->cols = 0;
  for (int i = 0; i < PIECE_SIZE; i++) {
    for (int j = 0; j < PIECE_SIZE; j++) {
      p->board[i][j] = '.';
    }
  }
}

void print_piece(Piece p) {
  printf("Name: %c; Size: %dx%d\n", p.name, p.rows, p.cols);
  for (int i = 0; i < PIECE_SIZE; ++i) {
    for (int j = 0; j < PIECE_SIZE; ++j) {
      printf("%c", p.board[i][j]);
    }
    printf("\n");
  }
}

void rotate_clockwise(Piece *p) {
  Piece temporal;
  init_piece(&temporal);
  for (int c = 0; c < PIECE_SIZE; c++) {
    for (int r = 0; r < PIECE_SIZE; r++) {
      temporal.board[c][p->rows - 1 - r] = p->board[r][c];
    }
  };
  for (int c = 0; c < PIECE_SIZE; c++) {
    for (int r = 0; r < PIECE_SIZE; r++) {
      p->board[c][r] = temporal.board[c][r];
    };
  };
  // memcpy(p->board, temporal.board, sizeof(temporal.board));
}

void rotate_counter_clockwise(Piece *p) {
  Piece temporal;
  init_piece(&temporal);
  for (int c = 0; c < PIECE_SIZE; c++) {
    for (int r = 0; r < PIECE_SIZE; r++) {
      temporal.board[r][c] = p->board[p->rows - 1 - c][r];
    }
  };
  for (int c = 0; c < PIECE_SIZE; c++) {
    for (int r = 0; r < PIECE_SIZE; r++) {
      p->board[c][r] = temporal.board[c][r];
    };
  };
  // memcpy(p->board, temporal.board, sizeof(temporal.board));
}

Piece make_O() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'O';
  piece.rows = 2;
  piece.cols = 2;
  piece.board[0][0] = '#';
  piece.board[0][1] = '#';
  piece.board[1][0] = '#';
  piece.board[1][1] = '#';
  return piece;
};
Piece make_I() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'I';
  piece.rows = 3;
  piece.cols = 1;
  piece.board[0][0] = '#';
  piece.board[0][1] = '#';
  piece.board[0][2] = '#';
  return piece;
};
Piece make_S() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'S';
  piece.rows = 2;
  piece.cols = 3;
  piece.board[0][1] = '#';
  piece.board[0][2] = '#';
  piece.board[1][0] = '#';
  piece.board[1][1] = '#';
  return piece;
};
Piece make_Z() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'Z';
  piece.rows = 2;
  piece.cols = 3;
  piece.board[0][0] = '#';
  piece.board[0][1] = '#';
  piece.board[1][1] = '#';
  piece.board[1][2] = '#';
  return piece;
};
Piece make_L() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'L';
  piece.rows = 3;
  piece.cols = 2;
  piece.board[0][0] = '#';
  piece.board[1][0] = '#';
  piece.board[2][0] = '#';
  piece.board[2][1] = '#';
  return piece;
};

Piece make_J() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'J';
  piece.rows = 3;
  piece.cols = 2;
  piece.board[0][1] = '#';
  piece.board[1][1] = '#';
  piece.board[2][0] = '#';
  piece.board[2][1] = '#';
  return piece;
};

Piece make_T() {
  Piece piece;
  init_piece(&piece);
  piece.name = 'T';
  piece.rows = 2;
  piece.cols = 3;
  piece.board[0][0] = '#';
  piece.board[0][1] = '#';
  piece.board[0][2] = '#';
  piece.board[1][1] = '#';
  return piece;
};
