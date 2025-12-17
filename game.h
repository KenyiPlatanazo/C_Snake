#ifndef GAME
#define GAME
#include "snake.h"
#include <SDL2/SDL.h>
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
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GRID_CELL_SIZE 36
typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Rect *rectangle;
  Snake snake;
  Board board;
  int direction;
  int game_over;
} Game;

// SNAKE functions
void update(Game *game);
Cell getNextCell(Game *game, Cell currentPosition);

// SDL functions
int sdl_initialize(Game *game);
void game_cleanup(Game *game, int exit_status);
#endif // !GAME
