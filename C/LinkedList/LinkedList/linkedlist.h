#pragma once

/* Generic implementation
typedef union data {
  char* string;
  int integer;
} dataValue;
*/

//General structure
typedef struct node {
  int data; 
  node* next;
} node;

//Single linked list
typedef struct linkedList {
  node* rootNode;
  node* lastNode;
  int size;
} linkedList;

//Creation of new linked list
linkedList* createLinkedList();

//Insertion of a node into a linked list
void insertNode(linkedList* list,int data);

//Deletion of a node in a linked list
void deleteNode(linkedList* list,int index);

//Retrieve an element from a linked list
int getElement(linkedList* list, int index);

//Does the list contain data
int listContains(linkedList* list, int data);

//Is the list empty
int listIsEmpty(linkedList* list);

//List size
int listSize(linkedList* list);

//Sort a linked list
void sortLinkedList(linkedList* list);

//Free linked list
void freeLinkedList(linkedList* list);