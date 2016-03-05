/*
 * matrix.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "matrix.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define index(ROW,COL,NUM_COLS) ((ROW * NUM_COLS) + COL)
#define RANGE 25

/* Creates a symmetrix matrix out of array */
void symmetricise(array2D *array) {

  srand(time(NULL));

  /* Randomise each value in the array */
  for (int row = 0; row < array->rows; row++) {
    for (int col = 0; col < array->cols; col++) {
      int r = (((RAND_MAX - rand()) % RANGE) + rand()) % RANGE;
      array->array[index(row, col, array->cols)] = r;
    }
  }

  /* Makes array[row][col] = array[col][row] */
  /* Only to need to swap the upper or lower triangular */

  int c = 1;
  for (int row = 0; row < array->rows; row++) {
    for (int col = c; col < array->cols; col++) {
      array->array[index(row, col, array->cols)] = array->array[index(col, row,
          array->cols)];
    }
    c++;
  }

}

/* Decomposes the matrix A into QR */
QR* QRdecompose(array2D *A) {

  /* Using the Gram-Schmidt process */

  QR* qr = malloc(sizeof(QR));
  array2D *Q = create2DArray((TYPE*)malloc(A->cols*A->rows*sizeof(TYPE)),A->rows,A->cols);
  array2D *R = create2DArray((TYPE*)malloc(A->cols*A->rows*sizeof(TYPE)),A->rows,A->cols);
  qr->Q = Q;
  qr->R = R;

  /* Obtain the orthonormal basis A */

  for (int i=0; i<A->cols; i++) {

    for (int j=0; j<=i; j++) {

    }

  }


  return qr;
}

/* Creates a 2D array and returns a pointer to the struct */
array2D* create2DArray(TYPE *array, int rows, int cols) {
  array2D *ary = malloc(sizeof(array2D));
  ary->array = array;
  ary->rows = rows;
  ary->cols = cols;
  return ary;
}

/* Debugging purposes only */
void printMatrix(array2D *arry) {
  for (int row = 0; row < arry->rows; row++) {
    printf("[");
    for (int col = 0; col < arry->cols - 1; col++) {
      printf(FLAG", ", arry->array[row * arry->cols + col]);
    }
    printf(FLAG, arry->array[row * arry->cols + arry->cols - 1]);
    printf("]\n");
  }
}
