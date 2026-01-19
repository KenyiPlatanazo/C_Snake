#include "SDL2/SDL.h"
#include "stdbool.h"
#include <SDL2/SDL_render.h>

#define WINDOWS_TITLE "Snake Game by a dummie"
#define GRID_CELL_SIZE 20
#define SCREEN_WIDTH ((ROW_COUNT * GRID_CELL_SIZE) + 1)
#define SCREEN_HEIGHT ((COL_COUNT * GRID_CELL_SIZE) + 1)
#define ROW_COUNT 29
#define COL_COUNT 23

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
  bool game_over;
};

void draw_grid(struct Game *game);
bool sdl_initialize(struct Game *game);
void game_cleanup(struct Game *game, int exit_status);
void init_board(struct Game *game);

int main() {
  struct Game game = {
      .window = NULL,
      .renderer = NULL,
      .game_over = false,
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
}

void draw_grid(struct Game *game) {
  // SDL_Color red = {255, 0, 0, 255};
  // SDL_Color green = {0, 255, 0, 255};
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 0};
  SDL_SetRenderDrawColor(game->renderer, white.r, white.g, white.b, white.a);
  SDL_RenderClear(game->renderer);
  SDL_Delay(16);
  for (int i = 0; i < ROW_COUNT; i++) {
    for (int j = 0; j < COL_COUNT; j++) {
      SDL_SetRenderDrawColor(game->renderer, black.r, black.g, black.b,
                             black.a);
      SDL_RenderDrawRect(game->renderer, &game->board[i][j].rect);
      SDL_RenderCopy(game->renderer, NULL, &game->board_frame,
                     &game->board[i][j].rect);
    }
  }
  SDL_RenderPresent(game->renderer);
}
