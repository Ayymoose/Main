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

  TYPE b[9] =
    {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

  matrix *ary = createMatrix(b,3,3);
  matrix *c = transpose(ary);

  printMatrix(c);

  return 0;
}
