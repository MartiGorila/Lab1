#include "main.h"

void run_game(Session *session) {
  GameState *game_state = &session->game_state;

  bool finish_game;

  do {
    // 1. Print data
    printf("Best score: %d\n", session->best_score);
    print_game_state(game_state);

    // 2. Select a move
    int game_option;
    do {
      print_options(game_state->board);
      printf("Enter a game option: ");
      game_option = read_int();
    } while (!is_valid_option(game_option));

    // 3.a Quit game
    if (game_option == QUIT_GAME) {
      return;
    }
    // 3.b Show best move
    if (game_option == SHOW_BEST_MOVE) {
      // ToDo in Lab 3
      continue;
    }

    // 3.c Run one turn with the given option
    run_turn(game_state, game_option);

    // 4. Update scores
    session->best_score = max(session->best_score, game_state->score);

    // 5. Add new number
    finish_game = is_terminal(game_state);
  } while (!finish_game);

  printf("*** GAME OVER ***\n");
  print_game_state(game_state);
}

void new_game(Session *session) {
  restart_session_game_state(session);
  run_game(session);
}

void save_game(Session *session) {
  char filename[100];
  printf("Enter the Name to save the game: ");
  scanf("%s", filename);

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for writing: %s\n", filename);
    return;
  }

  GameState *gs = &session->game_state;
  fprintf(file, "Score: %d\n", gs->score);
  PieceInfo *piece = &gs->current_piece;
  fprintf(file, "Current Piece Info:\n");
  fprintf(file, "Position: %d %d\n", piece->at_row, piece->at_col);
  // fprintf(file, "Piece Name: %s\n", piece->p.name);
  fprintf(file, "Piece Display:\n");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      fputc(piece->p.board[i][j], file);
      printf("%c", piece->p.board[i][j]);
    }
    fputc('\n', file);
    printf("\n");
  }
  fprintf(file, "Board Dimensions: %d %d\n", gs->rows, gs->columns);
  fprintf(file, "Board Display:\n");
  for (int i = 0; i < gs->rows; i++) {
    for (int j = 0; j < gs->columns; j++) {
      fputc(gs->board[i][j], file);
    }
    fputc('\n', file);
  }

  fclose(file);
}
void load_game(Session *session) {
  char filename[100];
  // This si similar to the inverse of the save game but also initiating the
  // game
  printf("Enter the filename to load the game: ");
  scanf("%s", filename);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file for reading: %s\n", filename);
    return;
  }

  GameState *gs = &session->game_state;
  fscanf(file, "Score: %d\n", &gs->score);
  PieceInfo *piece = &gs->current_piece;
  fscanf(file, "Current Piece Info:\n");
  fscanf(file, "Position: %d %d\n", &piece->at_row, &piece->at_col);
  // fscanf(file, "Piece Name: %s\n", piece->p.name);
  fscanf(file, "Piece Display:\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      piece->p.board[i][j] = fgetc(file);
    }
    fgetc(file);
  }

  fscanf(file, "Board Dimensions: %d %d\n", &gs->rows, &gs->columns);
  make_board(gs);
  fscanf(file, "Board Display:\n");
  for (int i = 0; i < gs->rows; i++) {
    for (int j = 0; j < gs->columns; j++) {
      gs->board[i][j] = fgetc(file);
    }
    fgetc(file);
  }
  fclose(file);
  printf("Game state loaded succesfully at: %s\n", filename);
}

void resume_game(Session *session) { run_game(session); }

void print_menu() {
  printf("Menu options:\n");
  printf(
      "\t1. New game.\n");  // LAB1 - basic lab for creating board, pieces and
                            // movements LAB1 - extend game with GameState data
                            // structure, current score, best score
                            //      - also add standard (4x4) with a posible
                            //      extension, read board from command line
  printf("\t2. Save game.\n");    // LAB2 - Writing file
  printf("\t3. Load game.\n");    // LAB2 - Reading file
  printf("\t4. Resume game.\n");  // LAB2 - Continue game after reading file
  printf("\t5. Exit.\n");         // Free all reserved memory!
}

void run(Session *session) {
  int option;
  do {
    print_menu();
    do {
      printf("Enter an integer (%d-%d): ", NEW_GAME, EXIT);
      option = read_int();
    } while (option < NEW_GAME || option > EXIT);

    switch (option) {
      case NEW_GAME:
        new_game(session);
        break;
      case SAVE_GAME:
        save_game(session);
        break;
      case LOAD_GAME:
        load_game(session);
        break;
      case RESUME_GAME:
        resume_game(session);
        break;
      case EXIT:
        free_game_state(&session->game_state);
        break;
    }
  } while (option != EXIT);
}

int main() {
  Session session;
  init_session(&session);
  run(&session);
  printf("Press Enter to exit...");
  getchar();
  return 0;
}
