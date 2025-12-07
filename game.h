#ifndef GAME
#define GAME
#include "snake.h"
#define DIRECTION_NONE 0
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1
#define DIRECTION_UP 2
#define DIRECTION_DOWN -2
typedef struct {
  Snake snake;
  Board board;
  int direction;
  int game_over;
} Game;

void update(Game *game);
Cell getNextCell(Game *game, Cell currentPosition);
#endif // !GAME
