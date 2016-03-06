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



  TYPE a[3][3] = { { 12, -51, 4 }, { 6, 167, -68 }, { -4, 24, -41 } };




  matrix *A = create_matrix_from_array(3,3,a);
  QR *qr = QRdecompose(A);
  print_matrix(qr->Q);
  print_matrix(qr->R);

/*
  TYPE b[1][3] = { { 12, -51, 4 }};
  matrix *B = create_matrix_from_array(1,3,b);

  print_matrix(B);
  print_matrix(matrix_transpose_column(B));*/


  return 0;
}

