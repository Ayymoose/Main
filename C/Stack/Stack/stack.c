#pragma once

#include <stdlib.h>

//Definitions
#define EMPTY_STACK 0
#define UNINITIALISED_STACK -1

//Header includes
#include "stack.h"

/*
  Stack Implementation in C
  Stack grows upwards instead of downwards
  Note: Change to downwards stack upon next revision
*/

//Create a new stack with size elements
stack* createStack(int size) {
  //Create a new stack
  stack* newStack = (stack*) malloc(sizeof(stack) * size);
  newStack->stackElement = NULL;
  newStack->stackSize = size;
  newStack->stackPointer = UNINITIALISED_STACK;
  newStack->numberOfElements = EMPTY_STACK;
  return newStack;
}

//Push an element onto the stack
void push(stack* stack, stackElement* stackElement) {
  stack->stackPointer++;
  stack->numberOfElements++;
  (stack + stack->stackPointer)->stackElement = stackElement;
}

//Pop an element from the stack and return the pointer to the element popped
stackElement* pop(stack* stack) {
  //Get the element from the stack
  //Note: pop() will not free the stackElement as the outside should handle this.
  stackElement* element = (stack + stack->stackPointer)->stackElement;
  stack->stackPointer--;
  stack->numberOfElements--;
  return element;
}

//Peek at the top of the stack
stackElement* peek(stack* stack) {
  return (stack + stack->stackPointer)->stackElement;
}

//Check if stack is empty
int stackIsEmpty(stack* stack) {
  return (stack->numberOfElements == EMPTY_STACK) | (stack->numberOfElements == UNINITIALISED_STACK);
}

//Stack size 
int stackSize(stack* stack) {
  return stack->stackSize + 1;
}

//The number of stack elements on the stack
int stackElements(stack* stack) {
  return stack->numberOfElements;
}

//Free an initialised stack
void freeStack(stack* stack) {
  //Free all the elements
  //Infinite loop if uninitialised stack 
  while (stack->numberOfElements--) {
    free(stack + stack->stackPointer--);
  }
}