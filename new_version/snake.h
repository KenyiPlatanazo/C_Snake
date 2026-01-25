#ifndef SNAKE
#define SNAKE
#define ROW_COUNT 29
#define COL_COUNT 23
#define STARTING_ROW (ROW_COUNT / 2)
#define STARTING_COL (COL_COUNT / 2)

enum cell_type { BOARD, FOOD, SNAKE_PART };
struct Cell {
  int x, y;
  enum cell_type type;
};

struct Node {
  struct Cell *cell;
  struct Node *next;
  struct Node *previous;
};

struct Linked_list {
  struct Node *head;
  struct Node *last;
};

void new_node(struct Linked_list *list, struct Cell *data);
void init_linked_list(struct Linked_list *list);
void grow(struct Linked_list *snake);
#endif // !LINKED_LIST
