/*
 * main.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, const char **argv) {

  // Create a random 3x3 symmetric matrix
  //array *a = symmetricise(3);

  double a[16];

  array2D* ary = create2DArray(a,4,4);

  symmetricise(ary);
  printMatrix(ary);

  return 0;
}
