#ifndef SNAKE
#define SNAKE
#include "SDL2/SDL.h"
#include "linked_list.h"
#define ROW_COUNT 23
#define COL_COUNT 29
#define TRUE 1
#define FALSE 0
enum CellType { EMPTY, FOOD, SNAKE_MODE };

typedef struct Cell {
  int row, col;
  enum CellType cellType;
} Cell;

// Board

typedef struct Board {
  Cell cells[ROW_COUNT][COL_COUNT];
} Board;

// Snake
typedef struct Snake {
  Cell head;
  LinkedList *snakePartList;
} Snake;

Snake *initSnake(Cell initPos);
void grow(Snake *snake);
void move(Snake *snake, Cell nextCell);
int checkCrash(LinkedList *list, Cell nextCell);

// Food
void generateFood(Board *board);

#endif // !SNAKE
