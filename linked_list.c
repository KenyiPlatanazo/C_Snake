#include "linked_list.h"
#include <stdlib.h>

void deleteNode(Node *node) { free(node); }
Node *newNode(LinkedList *list, Cell *data) {
  Node *newNode = malloc(sizeof(Node));
  newNode->data = data;
  if (list->head != NULL) {
    newNode->next = list->head;
  }
  list->head = newNode;
  return newNode;
}
LinkedList *newLinkedList() {
  LinkedList *newLinkedList = malloc(sizeof(LinkedList));
  newLinkedList->head = NULL;
  return newLinkedList;
}

Node deleteLast(LinkedList *list) {
  Node *currentNode = list->head;
  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  };
  Node lastNode = *currentNode;
  deleteNode(currentNode);
  return lastNode;
}
