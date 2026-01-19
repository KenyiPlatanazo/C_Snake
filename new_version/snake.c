// TODO: Reevaluar cómo funcionará el tablero y cómo manejar la comida
// Posible reintroducción del array para el tablero (Se tendrá que volver a
// cambiar la lógica de SDL)
#include "snake.h"
#include "assert.h"
#include "stdlib.h"
#include "time.h"

void new_node(struct Linked_list *list, struct Cell data) {
  assert((list->head == NULL) && (list->last == NULL));

  struct Node *new_node = malloc(sizeof *new_node);
  if (!new_node)
    return;
  new_node->cell = data;
  new_node->next = NULL;
  new_node->previous = NULL;

  if (list->last) {
    list->last->next = new_node;
  } else {
    list->head = new_node;
  }
  list->last = new_node;
}
void init_linked_list(struct Linked_list *list) {
  list->head = NULL;
  list->last = NULL;
}
struct Linked_list *init_snake(void) {
  struct Linked_list *snake = malloc(sizeof(struct Linked_list));
  if (!snake)
    return NULL;
  init_linked_list(snake);
  struct Cell new_cell = {
      .x = STARTING_ROW, .y = STARTING_COL, .type = SNAKE_PART};
  new_node(snake, new_cell);
  return snake;
}
void grow(struct Linked_list *snake) {
  struct Cell new_cell = {
      .type = SNAKE_PART, .x = snake->last->cell.x, .y = snake->last->cell.y};
  new_node(snake, new_cell);
}

struct Cell *init_food(void) {
  srand(time(NULL));
  struct Cell *new_food = malloc(sizeof *new_food);
  if (!new_food)
    return NULL;
  new_food->type = FOOD;
  new_food->x = rand() % ROW_COUNT;
  new_food->y = rand() % COL_COUNT;
  return new_food;
}
