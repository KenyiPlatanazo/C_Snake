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

// TODO: ACTUALLY IMPLEMENT SOMETHING THAT MAKES SENSE YOU DISGUSTING BLOAT
void draw_grid(Game *game) {
  SDL_Color grid_background = {22, 22, 22, 225};
  SDL_Color grid_line_color = {44, 44, 44, 225};
  SDL_Color snake_cell_color = {0, 255, 0, 225};
  SDL_Color food_cell_color = {255, 0, 0};

  // Dibuja el fondo
  SDL_SetRenderDrawColor(game->renderer, grid_background.r, grid_background.g,
                         grid_background.b, grid_background.a);
  SDL_RenderClear(game->renderer);
  // Dibujar las lineas
  SDL_SetRenderDrawColor(game->renderer, grid_line_color.r, grid_line_color.g,
                         grid_line_color.b, grid_line_color.a);
  for (int x = 0; x < ((1 + GRID_CELL_SIZE) * GRID_WIDTH);
       x += GRID_CELL_SIZE) {
    SDL_RenderDrawLine(game->renderer, x, 0, x, SCREEN_HEIGHT);
  }
  for (int y = 0; y < ((1 + GRID_HEIGHT) * GRID_CELL_SIZE);
       y += GRID_CELL_SIZE) {
    SDL_RenderDrawLine(game->renderer, 0, y, SCREEN_WIDTH, y);
  }
  Cell *current = &game->snake.head;
  while (current != NULL) {
    SDL_Rect cell = {
        .x = current->row,
        .y = current->col,
        .w = GRID_CELL_SIZE,
        .h = GRID_CELL_SIZE,
    };
    SDL_RenderFillRect(game->renderer, &cell);
  }
  SDL_SetRenderDrawColor(game->renderer, snake_cell_color.r, snake_cell_color.g,
                         snake_cell_color.b, snake_cell_color.a);
  SDL_RenderFillRect(game->renderer, &game->grid_cursor);
  SDL_RenderPresent(game->renderer);
}

void handle_movement_input(Game *game, SDL_Event event) {
  switch (event.key.keysym.scancode) {
  case SDL_SCANCODE_ESCAPE:
    game_cleanup(game, 0);
    break;
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    game->grid_cursor.y -= GRID_CELL_SIZE;
    break;
  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    game->grid_cursor.y += GRID_CELL_SIZE;
    break;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    game->grid_cursor.x -= GRID_CELL_SIZE;
    break;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    game->grid_cursor.x += GRID_CELL_SIZE;
    break;
  default:
    break;
  }
}

void handle_inputs(Game *game, SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    game_cleanup(game, EXIT_SUCCESS);
    break;
  case SDL_KEYDOWN:
    handle_movement_input(game, event);
    break;
  case SDL_MOUSEBUTTONDOWN:
    game->grid_cursor.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
    game->grid_cursor.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
    break;
  default:
    break;
  }
}
