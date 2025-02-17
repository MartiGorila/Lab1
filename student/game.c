#include "game.h"

/**** LAB 1 - given functions ****/
void print_game_state(GameState *gs) {
  printf("*** Game State ***\n");
  printf("Score=%d\n", gs->score);
  print_board(gs);
}

void print_options() {
  printf("Options:\n");
  printf("\t%d. Move left\n", MOVE_LEFT);
  printf("\t%d. Move right\n", MOVE_RIGHT);
  printf("\t%d. Rotate clockwise\n", ROTATE_CW);
  printf("\t%d. Rotate counter clockwise\n", ROTATE_CCW);
  printf("\t%d. None\n", NONE);
  printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
  printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(int option) {
  return ((MOVE_LEFT <= option) && (option <= QUIT_GAME));
}

void print_line(int columns) {
  for (int c = -1; c < columns + 1; ++c) printf("-");
  printf("\n");
}

void print_board(GameState *game_state) {
  Piece *piece = &game_state->current_piece.p;
  int p_row_size = piece->rows;
  int p_col_size = piece->cols;
  int current_row = game_state->current_piece.at_row;
  int current_col = game_state->current_piece.at_col;
  print_line(game_state->current_piece.at_col);
  for (int r = 0; r < MIN_ROWS; ++r) {
    if (r == 4) print_line(game_state->current_piece.at_col);
    printf("|");
    for (int c = 0; c < MIN_COLUMNS; ++c) {
      if ((game_state->board[r][c] == '.') && (current_row <= r) &&
          (r < current_row + p_row_size) && (current_col <= c) &&
          (c < current_col + p_col_size)) {
        printf("%c", piece->board[r - current_row][c - current_col]);
      } else
        printf("%c", game_state->board[r][c]);
    }
    printf("|\n");
  }
  print_line(game_state->current_piece.at_col);
  printf("\n");
}

void get_new_random_piece(GameState *game_state) {
  // Random piece
  switch (rand() % MAX_NUM_PIECES) {
    case 0:
      game_state->current_piece.p = make_I();
      break;
    case 1:
      game_state->current_piece.p = make_J();
      break;
    case 2:
      game_state->current_piece.p = make_L();
      break;
    case 3:
      game_state->current_piece.p = make_O();
      break;
    case 4:
      game_state->current_piece.p = make_S();
      break;
    case 5:
      game_state->current_piece.p = make_T();
      break;
    case 6:
      game_state->current_piece.p = make_Z();
      break;
    default:
      break;
  }

  // Random orientation
  int rotations = rand() % 3;
  for (int r = 0; r < rotations; ++r)
    rotate_clockwise(&(game_state->current_piece.p));
  game_state->current_piece.at_row = 4 - game_state->current_piece.p.rows;
  game_state->current_piece.at_col =
      rand() % (MIN_COLUMNS + 1 - game_state->current_piece.p.cols);
}

void block_current_piece(GameState *game_state) {
  Piece *piece = &game_state->current_piece.p;
  int row = game_state->current_piece.at_row;
  int col = game_state->current_piece.at_col;
  for (int i = 0; i < piece->rows; ++i)
    for (int j = 0; j < piece->cols; ++j)
      if (piece->board[i][j] == '#') game_state->board[row + i][col + j] = 'X';
}

bool is_collision(GameState *gs) {
  Piece *piece = &gs->current_piece.p;
  int p_row_size = piece->rows;
  int p_col_size = piece->cols;
  int row = gs->current_piece.at_row;
  int col = gs->current_piece.at_col;

  if ((row < 0) || (col < 0) || (row + p_row_size - 1 >= MIN_ROWS) ||
      (col + p_col_size - 1 >= MIN_COLUMNS))
    return true;  // piece is out of the grid

  for (int i = 0; i < piece->rows; ++i)
    for (int j = 0; j < piece->cols; ++j)
      if ((piece->board[i][j] == '#') && (gs->board[row + i][col + j] == 'X'))
        return true;  // piece collides with another structure in the board

  return false;
}

int remove_completed_lines(char **board) {
  int lines = 0;
  bool completed_line;
  for (int r = 4; r < MIN_ROWS; ++r) {
    completed_line = true;
    for (int c = 0; c < MIN_COLUMNS; ++c) {
      if (board[r][c] != 'X') {
        completed_line = false;
        break;
      }
    }
    if (completed_line) {
      ++lines;
      // Move all rows above, once down
      for (int r2 = r; r2 > 3; --r2) {
        for (int c = 0; c < MIN_COLUMNS; ++c) {
          board[r2][c] = board[r2 - 1][c];
        }
      }
    }
  }
  return lines;
}

/********************************************************/
/******* LAB 1 - functions to program (start here) ******/
/********************************************************/

void make_board(GameState *gs) {
  gs->board = (char **)malloc(gs->rows * sizeof(char *));
  if (gs->board == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  for (int i = 0; i < gs->rows; i++) {
    gs->board[i] = (char *)malloc(gs->columns * sizeof(char));
    if (gs->board[i] == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
    }
  }
}
void free_game_state(GameState *gs) {
  if (gs->board != NULL) {
    for (int i = 0; i < gs->rows; i++) {
      free(gs->board[i]);
    }
    free(gs->board);
    gs->board = NULL;
  }
}
void init_game_state(GameState *game_state) {
  game_state->board = NULL;
  game_state->rows = MIN_ROWS;
  game_state->columns = MIN_COLUMNS;
  make_board(game_state);
  set_default_game_state(game_state);
};  // starts the game

bool is_terminal(GameState *gs) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < gs->columns; j++) {
      if (gs->board[i][j] == 'X') {
        return true;
      }
    }
  }
  return false;
};
void restart_game_state(GameState *gs) {
  int rows, columns;

  printf("Enter the number of rows (greater than %d): ", MIN_ROWS);
  scanf("%d", &rows);
  while (rows < MIN_ROWS) {
    printf(
        "Number of rows should be greater than or equal to %d. Please enter "
        "again: ",
        MIN_ROWS);
    scanf("%d", &rows);
  }

  printf("Enter the number of columns (greater than %d): ", MIN_COLUMNS);
  scanf("%d", &columns);
  while (columns < MIN_COLUMNS) {
    printf(
        "Number of columns should be greater than or equal to %d. Please enter "
        "again: ",
        MIN_COLUMNS);
    scanf("%d", &columns);
  }

  make_board(gs);
  set_default_game_state(gs);
};
void set_default_game_state(GameState *gs) {
  gs->score = 0;
  for (int r = 0; r < gs->rows; r++) {
    for (int c = 0; c < gs->columns; c++) {
      gs->board[r][c] = '.';
    }
  }
  get_new_random_piece(gs);
};
void move_piece(GameState *gs, int option) {
  int dir = 0;
  if (option == MOVE_LEFT)
    dir = -1;
  else if (option == MOVE_RIGHT)
    dir = 1;
  else {
    printf("[ERROR] Invalid move option %d.\n", option);
    return;
  }

  int new_col = gs->current_piece.at_col + dir;
  if (new_col >= 0 && new_col < MIN_COLUMNS &&
      gs->board[gs->current_piece.at_row][new_col] == '.') {
    gs->current_piece.at_col = new_col;
  } else {
    printf("[ERROR] Collision or out of bounds. \n");
  }
};  // Move the piece left and right check for screen limit(columns)

void rotate_piece(GameState *game_state, int option) {
  if (option == ROTATE_CW)
    rotate_clockwise(&(game_state->current_piece.p));
  else if (option == ROTATE_CCW)
    rotate_counter_clockwise(&(game_state->current_piece.p));
  else {
    printf("[ERROR] Invalid rotation option %d. \n", option);
  }
  if (is_collision(game_state)) {
    if (option == ROTATE_CW) {
      rotate_counter_clockwise(&(game_state->current_piece.p));
    } else if (option == ROTATE_CCW) {
      rotate_clockwise(&(game_state->current_piece.p));
    }
  }
};  // Rotate pieces and check for aveliavility of the move
/********************************************************/
/******* LAB 1 - functions to program (end here) ********/

/********************************************************/

void run_turn(GameState *game_state, int option) {
  PieceInfo *p_inf = &(game_state->current_piece);
  if (option == MOVE_LEFT || option == MOVE_RIGHT)
    move_piece(game_state, option);
  else if (option == ROTATE_CW || option == ROTATE_CCW)
    rotate_piece(game_state, option);
  else if (option == NONE) {
  }  // do nothing
  else {
    printf("[ERROR] Invalid option %d.\n", option);
    exit(-3);
  }

  // Move down if possible, otherwise block the piece and remove
  // the completed lines, aggregating them to the current score.
  // If it is not in a terminal state, add a new random piece to the board.
  p_inf->at_row++;
  if (is_collision(game_state)) {
    p_inf->at_row--;
    block_current_piece(game_state);
    game_state->score += remove_completed_lines(game_state->board);
    if (!is_terminal(game_state)) get_new_random_piece(game_state);
  }
}
