#include "SDL2/SDL.h"
#include "snake.h"
#include "stdbool.h"
#include <SDL2/SDL_video.h>

#define WINDOWS_TITLE "Snake Game by a dummie"
#define GRID_CELL_SIZE 36
#define SCREEN_WIDTH ((ROW_COUNT * GRID_CELL_SIZE) + 1)
#define SCREEN_HEIGHT ((COL_COUNT * GRID_CELL_SIZE) + 1)

struct Tile {
  struct Cell cell;
  SDL_Rect rect;
};

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Linked_list snake;
  struct Tile board[ROW_COUNT][COL_COUNT];
  bool game_over;
};

void update(struct Game *game);
bool sdl_initialize(struct Game *game);
void game_cleanup(struct Game *game, int exit_status);
void draw_grid(struct Game *game);
void move(struct Game *game, SDL_Event event);
void handle_inputs(struct Game *game, SDL_Event event);
void init_board(struct Game *game);
