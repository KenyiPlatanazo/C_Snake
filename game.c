#include "game.h"
#include "snake.h"
#include <stdio.h>

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
