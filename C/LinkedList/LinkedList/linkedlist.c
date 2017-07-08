#include <stdlib.h>
#include "linkedlist.h"

#define EMPTY 0

//Creation of a new linked list
linkedList* createLinkedList() {
  linkedList* list = (linkedList*)malloc(sizeof(linkedList));
  list->rootNode = (node*)malloc(sizeof(node));
  list->lastNode = (node*)malloc(sizeof(node));
  list->rootNode->next = list->lastNode->next = NULL;
  list->rootNode->data = list->lastNode->data = NULL;
  list->size = EMPTY;
  return list;
}

//Insertion of a node O(1)
void insertNode(linkedList* list, int data) {

  //Create a new node
  node* newNode = (node*)malloc(sizeof(node));
  newNode->data = data;
  newNode->next = NULL;

  //If the list is empty
  if (listIsEmpty(list)) {
    //Point root and last node to this new node
    list->rootNode = list->lastNode = newNode;
  }
  else {
    list->lastNode->next = newNode;
    list->lastNode = newNode;
  }
  list->size++;
}

//Deletion of a node O(n)
void deleteNode(linkedList* list, int index) {
 
  //Assert: list is a valid initialised linkedlist and 0 <= index < list size
  //Optimise -> http://stackoverflow.com/questions/12914917/using-pointers-to-remove-item-from-singly-linked-list?rq=1

  //First find previous pointer to deleted node
  node* currentNode = list->rootNode;
  node* previousNode = currentNode;
  //3 Cases
  if (index == 0) {
    //1. Deleting the root node
    node* nextNode = list->rootNode->next;
    free(list->rootNode);
    list->rootNode = nextNode;
  }
  else if (index == listSize(list) - 1) {
    //2. Deleting the last node
    while (index--) { //Or currentNode != list->lastNode
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
    previousNode->next = NULL;
    free(list->lastNode);
    list->lastNode = previousNode;
  }
  else {
    //3. Deleting a node that is not the first or last
    while (index--) { //Or currentNode != list->lastNode
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
    previousNode->next = currentNode->next;
    free(currentNode);
  }
  //Decrement list size
  list->size--;
}

//Does the list contain data O(n)
int listContains(linkedList* list, int data) {
  node* currentNode = list->rootNode;
  while (currentNode) {
    if (currentNode->data == data) {
      return 1;
    }
    currentNode = currentNode->next;
  }
  return 0;
}

//Get an element from a linked list
int getElement(linkedList* list,int index) {
  if (index == 0) {
    return list->rootNode->data;
  }
  else if (index == listSize(list) - 1) {
    return list->lastNode->data;
  }
  else {
    node* currentNode = list->rootNode;
    while (index--) {
      currentNode = currentNode->next;
    }
    return currentNode->data;
  }
}

//Sort a linked list
void sortLinkedList(linkedList* list) {
  //Sorts list using a quick sort
}

//Size of the list
int listSize(linkedList* list) {
  return list->size;
}

//List is empty
int listIsEmpty(linkedList* list) {
  return (list->rootNode == NULL) | (listSize(list) == EMPTY);
}

//Free the linked list
void freeLinkedList(linkedList* list) {
  node* currentNode = list->rootNode;
  node* previousNode = currentNode;
  while (currentNode) {
    previousNode = currentNode;
    currentNode = currentNode->next;
    free(previousNode);
  }
}