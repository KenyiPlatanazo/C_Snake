#ifndef LINKED_LIST

#define LINKED_LIST
typedef struct Cell Cell;
typedef struct Node {
  Cell *data;
  struct Node *next;
} Node;

typedef struct LinkedList {
  Node *head;
} LinkedList;

void deleteNode(Node *node);
Node findNode(LinkedList *list);
Node *newNode(LinkedList *list, Cell *data);
LinkedList *newLinkedList();
Node deleteLast(LinkedList *list);

#endif // !LINKED_LIST
