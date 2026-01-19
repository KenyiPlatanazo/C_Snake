#ifndef SNAKE
#define SNAKE
#define ROW_COUNT 23
#define COL_COUNT 29
#define STARTING_ROW 13
#define STARTING_COL 15

enum cell_type { BOARD, FOOD, SNAKE_PART };
struct Cell {
  int x, y;
  enum cell_type type;
};

struct Node {
  struct Cell cell;
  struct Node *next;
  struct Node *previous;
};

struct Linked_list {
  struct Node *head;
  struct Node *last;
};

struct Cell *init_food(void);
void new_node(struct Linked_list *list, struct Cell data);
struct Linked_list *init_snake(void);
void init_linked_list(struct Linked_list *list);
void grow(struct Linked_list *snake);
#endif // !LINKED_LIST
