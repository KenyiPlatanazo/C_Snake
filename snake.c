#include "snake.h"
#include "linked_list.h"
#include <stdlib.h>
#include <time.h>

// Food
void generateFood(Board *board) {
  int row = 0, col = 0;
  srand(time(NULL));
  while (1) {
    row = (rand() % ROW_COUNT) + 1;
    col = (rand() % COL_COUNT) + 1;
    if (board->cells[row][col].cellType != SNAKE_MODE) {
      break;
    }
  }
  board->cells[row][col].cellType = FOOD;
}

// Snake
Snake *initSnake(Cell initPos) {
  Snake *snake = malloc(sizeof(Snake));
  snake->head = initPos;
  snake->snakePartList = newLinkedList();
  newNode(snake->snakePartList, &snake->head);
  snake->head.cellType = SNAKE_MODE;
  return snake;
}
void grow(Snake *snake) { newNode(snake->snakePartList, &snake->head); }
void move(Snake *snake, Cell nextCell) {
  Cell *tail = deleteLast(snake->snakePartList).data;
  tail->cellType = EMPTY;

  snake->head = nextCell;
  snake->head.cellType = SNAKE_MODE;
  newNode(snake->snakePartList, &snake->head);
}
int checkCrash(LinkedList *list, Cell nextCell) {
  Node *currentNode = list->head;
  while (currentNode->next != NULL) {
    if (currentNode->data->cellType == nextCell.cellType &&
        currentNode->data->col == nextCell.col &&
        currentNode->data->row == nextCell.row) {
      return TRUE;
    }
    currentNode = currentNode->next;
  };
  return FALSE;
}
