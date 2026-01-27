#include "SDL2/SDL.h"
#include "snake.h"
#include "stdbool.h"
#include <SDL2/SDL_video.h>

#define WINDOWS_TITLE "Snake Game by a dummie"
#define GRID_CELL_SIZE 20
#define SCREEN_WIDTH ((ROW_COUNT * GRID_CELL_SIZE) + 1)
#define SCREEN_HEIGHT ((COL_COUNT * GRID_CELL_SIZE) + 1)

struct Tile {
  struct Cell cell;
  SDL_Rect rect;
};

struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Linked_list *snake;
  struct Tile board[ROW_COUNT][COL_COUNT];
  struct Cell *food;
  bool game_over;
};

bool sdl_initialize(struct Game *game);
void game_cleanup(struct Game *game, int exit_status);
void draw_grid(struct Game *game);
void change_direction(struct Game *game, SDL_Event event);
void handle_inputs(struct Game *game);
void init_board(struct Game *game);
void create_food(struct Game *game);
void update_snake(struct Node *node, struct Cell *previous_cell);
struct Linked_list *init_snake(struct Game *game);
