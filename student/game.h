#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "pieces.h"
#include "utils.h"

/// ToDo in LAB 1 - define macros MAX_ROWS and MAX_COLUMNS  DONE
#define MIN_ROWS 8
#define MIN_COLUMNS 5
#define MAX_DEPTH 7
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
void free_game_state(GameState *gs);
void print_game_state(GameState *gs);
void print_options();
bool is_valid_option(int option);
void print_line();
void print_board(GameState *game_state);
void get_new_random_piece(GameState *game_state);
void block_current_piece(GameState *game_state);
bool is_collision(GameState *gs);
void make_board(GameState *gs);
/**** LAB 1 - functions to program (start here) ****/
void init_game_state(GameState *game_state);
void restart_game_state(GameState *gs);
void set_default_game_state(GameState *gs);
bool is_terminal(GameState *gs);  // True if contains X

// values in TOP-4 rows
void move_piece(GameState *gs, int option);

void rotate(GameState *gs, int option);

/**** LAB 1 - functions to program (end here) ****/

/// Implemented functions
void run_turn(GameState *game_state, int option);

int recursive_best_score(GameState *game_state, int depth);{
  if(depth >= MAX_DEPTH || is_terminal(game_state)){
    return game_state->score;
  }
  int best_score = game_state->score;
  int moves[] = {MOVE_LEFT, MOVE_RIGHT, ROTATE_CW, ROTATE_CCW, NONE};

  for(int i = 0; i < 5; i++) {
    GameState *copy_gs = (GameState *)malloc(sizeof(GameState));
    if (copy_gs == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
    }
  }

    // Copy the current game state
    memcpy(copy_gs, game_state, sizeof(GameState));

    copy_gs->board = (char **)malloc(copy_gs->rows * sizeof(char *));
    for (int r = 0; r < copy_gs->rows; r++) {
      copy_gs->board[r] = (char *)malloc(copy_gs->columns * sizeof(char));
      memcpy(copy_gs->board[r], game_state->board[r], copy_gs->columns * sizeof(char));
    }

    run_turn(copy_gs, moves[i]); // Simulate the move
    int score = recursive_best_score(copy_gs, depth + 1); // Calculate the best score for the resulting state

    // Update the best score
    if(score > best_score) {
      best_score = score;
    }

    for (int r = 0; r < copy_gs->rows; r++) { // Free the copied game state
      free(copy_gs->board[r]);
    }
    free(copy_gs->board);
    free(copy_gs);
  }
  return best_score;


GameState copy(GameState *game_state);
int recursive_best_score(GameState *game_state, int depth);
int show_best_move(GameState *game_state);

#endif
