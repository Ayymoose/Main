#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(int argc, char** argv) {

  stack* myStack = createStack(2);

  stackElement* n = (stackElement*)malloc(sizeof(stackElement));
  n->string = "Big";
  push(myStack, n);
  stackElement* m = (stackElement*)malloc(sizeof(stackElement));
  m->string = "Enormous";
  push(myStack,m);

  printf("Stack size: \t%d\n", stackSize(myStack));
  printf("# of stack elements: \t%d\n", stackElements(myStack));
  printf("Stack is empty?: %d\n", stackIsEmpty(myStack));

  stackElement* s = pop(myStack);
  printf("%s\n", s->string);

  s = pop(myStack);
  printf("%s\n", s->string);

  printf("Stack size: \t%d\n", stackSize(myStack));
  printf("# of stack elements: \t%d\n", stackElements(myStack));
  printf("Stack is empty?: %d\n", stackIsEmpty(myStack));
  freeStack(myStack);


  getchar();


  return 0;
}