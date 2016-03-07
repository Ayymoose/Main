/*
 * main.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "defines.h"

int main(int argc, const char **argv) {



  TYPE a[3][3] = { { 12, -51, 4 }, { 6, 167, -68 }, { -4, 24, -41 } };

  matrix *A = create_matrix_from_array(3,3,a);
  matrix *Q = create_matrix(3,3);
  matrix *R = create_matrix(3,3);
  QRdecompose(A,Q,R);

  print_matrix(A);
  print_matrix(Q);
  print_matrix(R);

  /*matrix *m = create_matrix(4,4);
  symmetricise(m);
  print_matrix(m);
  free_matrix(m);*/



  return 0;
}

