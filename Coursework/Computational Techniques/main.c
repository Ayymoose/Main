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

 /*TYPE a[9] =
  {
      12, -51, 4,
      6, 167, -68,
      -4, 24, -41
  };

  TYPE b[9] =
    {
        1, 2, 3,
    };*/

  int a[3][3] =
  {
      {1,2,3},
      {4,5,6},
      {7,8,9},
  };

  int b[3][3] =
  {
        {9,7,8},
        {6,5,4},
        {3,2,1},
  };

  //matrix *ary = create_matrix(b,1,3);
  //matrix *c = transpose(ary);

  matrix *m1 = create_matrix_from_array(3,3,a);
  matrix *m2 = create_matrix_from_array(3,3,b);
  matrix *m3 = matrix_multiply(m1,m2);

  print_matrix(m3);

  free_matrix(m1);
  free_matrix(m2);
  free_matrix(m3);


  return 0;
}
