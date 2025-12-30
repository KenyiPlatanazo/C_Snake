#ifndef GAME
#define GAME
#include "snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// SNAKE movement
#define DIRECTION_NONE 0
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1
#define DIRECTION_UP 2
#define DIRECTION_DOWN -2

// SDL2
#define WINDOWS_TITLE "Snake Game by a dummie"
#define GRID_CELL_SIZE 36
#define GRID_WIDTH 29
#define GRID_HEIGHT 23
#define CELL_STARTING_HEIGHT 12
#define CELL_STARTING_WIDTH 14
#define SCREEN_WIDTH ((GRID_WIDTH * GRID_CELL_SIZE) + 1)
#define SCREEN_HEIGHT ((GRID_HEIGHT * GRID_CELL_SIZE) + 1)

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect *rectangle;
  Snake snake;
  Board board;
  int direction;
  int game_over;
  SDL_Rect grid_cursor;
} Game;

// SNAKE functions
void update(Game *game);
Cell getNextCell(Game *game, Cell currentPosition);

// SDL functions
int sdl_initialize(Game *game);
void game_cleanup(Game *game, int exit_status);
void draw_grid(Game *game);
void handle_movement_input(Game *game, SDL_Event event);
void handle_inputs(Game *game, SDL_Event event);
#endif // !GAME
