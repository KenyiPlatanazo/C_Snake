#include "game.h"
#include "snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int main() { return 0; }

void update(Game *game) {
  if (game->game_over == TRUE) {
    return;
  };
  if (game->direction != DIRECTION_NONE) {
    Cell nextCell = game->snake.head;
    if (checkCrash(game->snake.snakePartList, nextCell)) {
      game->direction = DIRECTION_NONE;
      game->game_over = TRUE;
    } else {
      move(&game->snake, nextCell);
      if (nextCell.cellType == FOOD) {
        grow(&game->snake);
        generateFood(&game->board);
      }
    }
  }
}
Cell getNextCell(Game *game, Cell currentPosition) {
  int row = currentPosition.row;
  int col = currentPosition.col;
  switch (game->direction) {
  case DIRECTION_RIGHT:
    col++;
    break;
  case DIRECTION_LEFT:
    col--;
    break;
  case DIRECTION_UP:
    row--;
    break;
  case DIRECTION_DOWN:
    row++;
    break;
  }

  Cell nextCell = game->board.cells[row][col];
  return nextCell;
}

int sdl_initialize(Game *game) {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return TRUE;
  }
  game->window =
      SDL_CreateWindow(WINDOWS_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  if (!game->window) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return TRUE;
  }
  game->renderer = SDL_CreateRenderer(game->window, -1, 0);
  if (!game->renderer) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return TRUE;
  }
  game->rectangle->x = (ROW_COUNT - 1) / (2 * GRID_CELL_SIZE);
  game->rectangle->y = (ROW_COUNT - 1) / (2 * GRID_CELL_SIZE);
  game->rectangle->w = GRID_CELL_SIZE;
  game->rectangle->h = GRID_CELL_SIZE;
  return FALSE;
}
void game_cleanup(Game *game, int exit_status) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  exit(1);
}
