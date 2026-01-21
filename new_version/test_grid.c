#include "SDL2/SDL.h"
#include "stdbool.h"
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#define WINDOWS_TITLE "Snake Game by a dummie"
#define GRID_CELL_SIZE 20
#define SCREEN_WIDTH ((ROW_COUNT * GRID_CELL_SIZE) + 1)
#define SCREEN_HEIGHT ((COL_COUNT * GRID_CELL_SIZE) + 1)
#define ROW_COUNT 29
#define COL_COUNT 23
#define UP 1
#define DOWN -1
#define RIGHT 1
#define LEFT -1

enum Color { RED, GREEN, GREY };

struct Cell {
  enum Color color;
  int x, y;
};

struct Tile {
  struct Cell cell;
  SDL_Rect rect;
};

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Tile board[ROW_COUNT][COL_COUNT];
  SDL_Rect board_frame;
  struct Cell *head;
  bool game_over;
};

void draw_grid(struct Game *game);
bool sdl_initialize(struct Game *game);
void game_cleanup(struct Game *game, int exit_status);
void init_board(struct Game *game);
void handle_movement_input(struct Game *game, SDL_Event event);
void handle_inputs(struct Game *game, SDL_Event event);
void check_crash(struct Game *game);
void move_head(struct Game *game, int movement);

int main() {
  struct Game game = {
      .window = NULL,
      .renderer = NULL,
      .game_over = false,
      .head = NULL,
  };
  if (sdl_initialize(&game)) {
    game_cleanup(&game, EXIT_FAILURE);
    printf("We fucked up >:c");
    exit(1);
  }
  while (true) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        game_cleanup(&game, EXIT_SUCCESS);
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
          game_cleanup(&game, EXIT_SUCCESS);
          break;
        case SDL_SCANCODE_SPACE:
          SDL_SetRenderDrawColor(game.renderer, rand() % 256, rand() % 256,
                                 rand() % 256, rand() % 256);
          break;
        default:
          break;
        }
      default:
        break;
      }
    }
  }
  return 0;
}

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
    return true;
  }
  game->renderer = SDL_CreateRenderer(game->window, -1, 0);
  if (!game->renderer) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return true;
  }
  init_board(game);
  draw_grid(game);
  return false;
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
      game->board[i][j].cell.color = GREY;
      game->board[i][j].cell.x = i;
      game->board[i][j].cell.y = j;
      game->board[i][j].rect.x = i * GRID_CELL_SIZE;
      game->board[i][j].rect.y = j * GRID_CELL_SIZE;
      game->board[i][j].rect.w = GRID_CELL_SIZE;
      game->board[i][j].rect.h = GRID_CELL_SIZE;
    }
  }
  game->board_frame.x = 0;
  game->board_frame.y = 0;
  game->board_frame.w = SCREEN_HEIGHT;
  game->board_frame.h = SCREEN_HEIGHT;
  // For the demonstration, the moving cell will always start in the middle of
  // the grid
  game->head = &game->board[ROW_COUNT / 2][COL_COUNT / 2].cell;
}

void draw_grid(struct Game *game) {
  // SDL_Color red = {255, 0, 0, 255};
  // SDL_Color green = {0, 255, 0, 255};
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 0};
  SDL_Delay(16);
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COL_COUNT; j++) {
      // Fills the cell with color
      SDL_SetRenderDrawColor(game->renderer, white.r, white.g, white.b,
                             white.a);
      SDL_RenderFillRect(game->renderer, &game->board[i][j].rect);
      // Adds a black frame to each cell of the grid
      SDL_SetRenderDrawColor(game->renderer, black.r, black.g, black.b,
                             black.a);
      SDL_RenderDrawRect(game->renderer, &game->board[i][j].rect);
      SDL_RenderCopy(game->renderer, NULL, &game->board_frame,
                     &game->board[i][j].rect);
    }
  }
  SDL_RenderPresent(game->renderer);
}

void handle_movement_input(struct Game *game, SDL_Event event) {
  switch (event.key.keysym.scancode) {
  case SDL_SCANCODE_ESCAPE:
    game_cleanup(game, 0);
    break;
  case SDL_SCANCODE_W:
  case SDL_SCANCODE_UP:
    if (game->head->y - 1 < 0)
      game_cleanup(game, EXIT_FAILURE);
    game->head->y = game->head->y - 1;
    game->board[game->head->y][game->head->y].cell.color = GREEN;
    break;
  case SDL_SCANCODE_S:
  case SDL_SCANCODE_DOWN:
    if (game->head->y + 1 >= COL_COUNT)
      game_cleanup(game, EXIT_FAILURE);
    game->head->y = game->head->y + 1;
    game->board[game->head->y][game->head->y].cell.color = GREEN;
    break;
  case SDL_SCANCODE_A:
  case SDL_SCANCODE_LEFT:
    if (game->head->x - 1 < 0)
      game_cleanup(game, EXIT_FAILURE);
    game->head->x = game->head->x - 1;
    game->board[game->head->x][game->head->x].cell.color = GREEN;
    break;
  case SDL_SCANCODE_D:
  case SDL_SCANCODE_RIGHT:
    if (game->head->y + 1 >= ROW_COUNT)
      game_cleanup(game, EXIT_FAILURE);
    game->head->x = game->head->x + 1;
    game->board[game->head->x][game->head->x].cell.color = GREEN;
    break;
  default:
    break;
  }
}
void handle_inputs(struct Game *game, SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    game_cleanup(game, EXIT_SUCCESS);
    break;
  case SDL_KEYDOWN:
    handle_movement_input(game, event);
    break;
  default:
    break;
  }
}
void check_crash(struct Game *game) {

  int movement = 1;
  switch (movement) {
  case DOWN:
    movement = movement * -1;
  case UP:
    if (game->head->y + movement >= COL_COUNT || game->head->y + movement < 0) {
      game_cleanup(game, EXIT_FAILURE);
    }
    move_head(game, movement);
    break;
  case LEFT:
    movement = movement * -1;
  case RIGHT:
    if (game->head->x + movement >= ROW_COUNT || game->head->x + movement < 0)
      game_cleanup(game, EXIT_FAILURE);
    move_head(game, movement);
  default:
    break;
  }
}
void move_head(struct Game *game, int movement) {}
