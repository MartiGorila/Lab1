#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "pieces.h"
#include "utils.h"

/// ToDo in LAB 1 - define macros MAX_ROWS and MAX_COLUMNS  DONE
#define MIN_ROWS 8
#define MIN_COLUMNS 5
typedef struct {
  // ToDo in LAB 1 - define data structure DONE
  Piece p;
  int at_row;
  int at_col;
} PieceInfo;

typedef struct GameState {
  int score;
  char **board;
  PieceInfo current_piece;
  int rows;
  int columns;
  // ToDo in LAB 1 - define data structure DONE
} GameState;

/// Implemented functions
void print_game_state(GameState *gs);
void print_options();
bool is_valid_option(int option);
void print_line();
void print_board(GameState *game_state);
void get_new_random_piece(GameState *game_state);
void block_current_piece(GameState *game_state);
bool is_collision(char **board, PieceInfo *piece_info);

/**** LAB 1 - functions to program (start here) ****/
void init_game_state(GameState *game_state);

bool is_terminal(char **board);  // True if contains X

// values in TOP-4 rows
void move_piece(char **board, PieceInfo *piece_info, int option);

void rotate(char **board, PieceInfo *piece_info, int option);

/**** LAB 1 - functions to program (end here) ****/

/// Implemented functions
void run_turn(GameState *game_state, int option);

#endif
