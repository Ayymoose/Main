/*
 * matrix.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "matrix.h"
#include "vector.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define index(ROW,COL,NUM_COLS) ((ROW * NUM_COLS) + COL)
#define RANGE 25

/* Creates a symmetrix matrix out of array */
void symmetricise(matrix *array) {

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

/* Matrix multiplication (m1 * m2) */
matrix* matrixMultiply(matrix *m1, matrix *m2) {

  /* Remove for performance */
  assert(m1->cols == m2->rows);

  /* Result matrix */
  matrix *m3 = createMatrix((TYPE*)malloc(m1->rows * m2->cols * sizeof(TYPE)),m1->rows,m2->cols);

  TYPE sum = 0;

  /* Naive multiplication */
  for (int row=0; row<m1->rows; row++) {
    for (int col=0; col<m2->cols; col++) {
      for (int k=0; k<m1->cols; k++) {
        sum += m1->array[index(k,col,m1->cols)] * m2->array[index(row,k,m2->cols)];
      }
      m3->array[index(row,col,m3->cols)] = sum;
      sum = 0;
    }
  }
  return m3;
}

/* Matrix transpose */
matrix* transpose(matrix* m) {
  matrix *mt = createMatrix((TYPE*)malloc(m->rows*m->cols*sizeof(TYPE)),m->cols,m->rows);
  for (int row=0; row<m->rows; row++) {
    for (int col=0; col<m->cols; col++) {
      mt->array[index(col,row,mt->cols)] = m->array[index(row,col,m->cols)];
    }
  }
  return mt;
}

/* Decomposes the matrix A into QR */
QR* QRdecompose(matrix *A) {

  /* Using the Gram-Schmidt process */

  QR* qr = malloc(sizeof(QR));
  matrix *Q = createMatrix((TYPE*) malloc(A->cols * A->rows * sizeof(TYPE)),
      A->rows, A->cols);
  matrix *R = createMatrix((TYPE*) malloc(A->cols * A->rows * sizeof(TYPE)),
      A->rows, A->cols);
  qr->Q = Q;
  qr->R = R;

  /* Obtain the orthonormal basis A */


  for (int i = 0; i < A->cols; i++) {



    for (int j = 0; j <= i; j++) {



    }



  }

  return qr;
}

/* Creates a 2D array and returns a pointer to the struct */
matrix* createMatrix(TYPE *array, int rows, int cols) {
  matrix *ary = malloc(sizeof(matrix));
  ary->array = array;
  ary->rows = rows;
  ary->cols = cols;
  return ary;
}

/* Debugging purposes only */
void printMatrix(matrix *arry) {
  for (int row = 0; row < arry->rows; row++) {
    printf("[");
    for (int col = 0; col < arry->cols - 1; col++) {
      printf(FLAG", ", arry->array[row * arry->cols + col]);
    }
    printf(FLAG, arry->array[row * arry->cols + arry->cols - 1]);
    printf("]\n");
  }
}
