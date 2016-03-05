/*
 * main.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "defines.h"

int main(int argc, const char **argv) {

  TYPE a[9] =
  {
      12, -51, 4,
      6, 167, -68,
      -4, 24, -41
  };

  array2D *ary = create2DArray(a,3,3);
  vector *v = vectorFromColumn(ary,0);

  normalise(v);

  printVector(v);

  //symmetricise(ary);
  printMatrix(ary);

  return 0;
}
