#pragma once

//Function prototypes

//Generic stack
typedef union stackElement {
  const char* string;
  int integer;
} stackElement;

typedef struct stack {
  stackElement* stackElement;  /* A generic stack element */
  int stackPointer;            /* The stack pointer */
  int stackSize;               /* The size of a stack (not including the number of elements) */
  int numberOfElements;        /* Number of elements in the stack */
} stack;

//Create a new stack with size elements
stack* createStack(int size);

//Push an element onto the stack
void push(stack* stack, stackElement* stackElement);

//Pop an element from the stack and return the element popped
stackElement* pop(stack* stack);

//Peek at the top of the stack
stackElement* peek(stack* stack);

//Check if stack is empty
int stackIsEmpty(stack* stack);

//Stack size 
int stackSize(stack* stack);

//Number of elements in the stack
int stackElements(stack* stack);

//Free an initialised stack
void freeStack(stack* stack);