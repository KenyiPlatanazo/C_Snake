// TODO: Reevaluar cómo funcionará el tablero y cómo manejar la comida
// Posible reintroducción del array para el tablero (Se tendrá que volver a
// cambiar la lógica de SDL)
#include "snake.h"
#include "assert.h"
#include "stdlib.h"
#include "time.h"

void new_node(struct Linked_list *snake, struct Cell *cell) {
  struct Node *new_node = malloc(sizeof *new_node);
  assert(new_node);
  new_node->cell = cell;
  new_node->next = snake->head;
  new_node->previous = NULL;

  if (snake->head) {
    snake->head->previous = new_node;
  } else {
    snake->last = new_node;
  }
  snake->head = new_node;
}
void init_linked_list(struct Linked_list *list) {
  list->head = NULL;
  list->last = NULL;
}

void delete_tail(struct Linked_list *snake) {
  assert(snake->last);
  struct Node *tail = snake->last;
  tail->cell->type = BOARD;
  snake->last = tail->previous;
  snake->last->next = NULL;
  free(tail);
}
