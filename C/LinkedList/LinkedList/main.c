#include <stdio.h>

#pragma warning (disable : 4996)

#include "linkedlist.h"

int main(int argc, char** argv) {

  linkedList* ints = createLinkedList();
  insertNode(ints, 10);
  insertNode(ints, 15);
  insertNode(ints, 18);
  insertNode(ints, 56);
  insertNode(ints, 64);
  insertNode(ints, 3142);
  insertNode(ints, 90);

  //Iterate over list
  node* currentNode = ints->rootNode;
  while (currentNode) {
    printf("%d\n", currentNode->data);
    currentNode = currentNode->next;
  }

  freeLinkedList(ints);
  getchar();

  return 0;
}