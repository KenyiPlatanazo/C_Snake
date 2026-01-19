#include "game.h"
#include "assert.h"
#include "snake.h"
#include <SDL2/SDL_video.h>

void update(struct Game *game);
bool sdl_initialize(struct Game *game) {

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return true;
  }
  game->window =
      SDL_CreateWindow(WINDOWS_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!game->window) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }
  game->renderer = SDL_CreateRenderer(game->window, -1, 0);
  if (!game->renderer) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return true;
  }
  draw_grid(game);
  return true;
}
void game_cleanup(struct Game *game, int exit_status) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  exit(1);
}
void init_board(struct Game *game) {
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COL_COUNT; j++) {
      game->board[i][j].cell.type = BOARD;
      game->board[i][j].cell.x = i;
      game->board[i][j].cell.y = j;
      game->board[i][j].rect.x = (ROW_COUNT - 1) / (2 * GRID_CELL_SIZE);
      game->board[i][j].rect.y = (COL_COUNT - 1) / (2 * GRID_CELL_SIZE);
      game->board[i][j].rect.w = GRID_CELL_SIZE;
      game->board[i][j].rect.h = GRID_CELL_SIZE;
    }
  }
}

// TODO: Make a better assertion to make sure the board is correctly initialized
void draw_grid(struct Game *game) { assert(game->board == NULL); }
void move(struct Game *game, SDL_Event event);
void handle_inputs(struct Game *game, SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    game_cleanup(game, EXIT_SUCCESS);
    break;
  case SDL_KEYDOWN:
    move(game, event);
    break;
    /*
case SDL_MOUSEBUTTONDOWN:
  game->grid_cursor.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
  game->grid_cursor.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
  break;
    */
  default:
    break;
  }
}
