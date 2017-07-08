/*
 * matrix.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "matrix.h"

#include <math.h>
//#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Change to adjust the maximum random value */
#define RANGE 50

/* Returns a random TYPE */
TYPE myrandom() {
  return (((RAND_MAX - rand()) % RANGE) + rand()) % RANGE;
}

/* Creates a random symmetrix matrix */
matrix* symmetricise(matrix *m) {

  srand(time(NULL));

  /* Create a random TYPE and then duplicate the type across the
     lower diagonal. Fill the diagonal with a random number. */
  for (int row = 0, c = 1; row < m->rows; row++) {
    for (int col = c; col < m->cols; col++) {
      m->array[col][row] = (TYPE)myrandom();
      m->array[row][col] = m->array[col][row];
    }
    m->array[row][row] = myrandom();
    c++;
  }
  return m;
}

/* Checks if a matrix is diagonal */
bool matrix_is_diagonal(const matrix *m) {
  for (int row=0; row<m->rows; row++) {
    for (int col=0; col<m->cols; col++) {
      if (row != col) {
        if (fabs(m->array[row][col]) > EPSILON) {
          return false;
        }
      } else {
        continue;
      }
    }
  }
  return true;
}

/* Matrix multiplication m3 = (m1 * m2) */
matrix* matrix_multiply(const matrix *m1, const matrix *m2, matrix *m3) {

  /* Remove for performance */
  //assert(m1->cols == m2->rows);

  TYPE sum = 0;

  /* Naive multiplication */
  for (int row = 0; row < m1->rows; row++) {
    for (int col = 0; col < m2->cols; col++) {
      for (int k = 0; k < m1->cols; k++) {
        sum += m1->array[row][k] * m2->array[k][col];
      }
      m3->array[row][col] = sum;
      sum = 0;
    }
  }
  return m3;
}

/* Adds two (square) matrices together m3 = m1 + m2 */
matrix* matrix_add(const matrix *m1, const matrix *m2, matrix *m3) {
  for (int row = 0; row < m3->rows; row++) {
    for (int col = 0; col < m3->cols; col++) {
      m3->array[row][col] = m1->array[row][col] + m2->array[row][col];
    }
  }
  return m3;
}

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void matrix_copy_column(const matrix *msrc, int col1, matrix *mdst, int col2) {
  for (int i = 0; i < msrc->rows; i++) {
    mdst->array[i][col2] = msrc->array[i][col1];
  }
}

/* Divides the matrix column c in m by k */
matrix* matrix_column_divide(matrix *m, int c, TYPE k) {
  for (int i = 0; i < m->rows; i++) {
    m->array[i][c] /= k;
  }
  return m;
}

/* Multiplies the matrix column c in m by k */
matrix* matrix_column_multiply(matrix *m, int c, TYPE k) {
  for (int i = 0; i < m->rows; i++) {
    m->array[i][c] *= k;
  }
  return m;
}

/* Subtracts m2's column c2 from m1's column c1 */
matrix* matrix_column_subtract(matrix *m1, int c1, const matrix *m2, int c2) {
  for (int i = 0; i < m1->rows; i++) {
    m1->array[i][c1] -= m2->array[i][c2];
  }
  return m1;
}

/* Returns the length of the matrix column in m */
double vector_length(const matrix *m, int column) {
  double length = 0;
  for (int row = 0; row < m->rows; row++) {
    length += m->array[row][column] * m->array[row][column];
  }
  return sqrt(length);
}

/* Decomposes the matrix A into QR */
void QRdecompose(const matrix *A, matrix *Q, matrix *R) {

  /* Using the Gram-Schmidt process */

  /* Temporary matrix T used in calculations */
  matrix *T = matrix_create(A->rows, 1);

  for (int i = 0; i < A->cols; i++) {

    //Qi = Ui
    matrix_copy_column(A, i, Q, i);

    for (int j = 0; j < i; j++) {

      //r[j,i] = Qj^T * Ui
      matrix_copy_column(Q, j, T, 0);
      TYPE r = 0;

      // Compute the multiplication of two Nx1 1xN matrices
      for (int k = 0; k < A->rows; k++) {
        r += Q->array[k][j] * A->array[k][i];
      }

      R->array[j][i] = r;
      matrix_column_subtract(Q, i, matrix_column_multiply(T, 0, r), 0);
      //

    }

    //r[i,i] = ||Qi||
    R->array[i][i] = vector_length(Q, i);
    //Qi = Qi/r[i,i]
    matrix_column_divide(Q, i, R->array[i][i]);
  }

  free_matrix(T);

}

/* Creates a matrix and returns a pointer to the struct */
matrix* matrix_create(int rows, int cols) {

  /* Allocate memory for the matrix struct */
  matrix *array = malloc(sizeof(matrix));
  array->rows = rows;
  array->cols = cols;

  /* Allocate enough memory for all the rows in the first matrix */
  array->array = calloc(rows, sizeof(TYPE*));

  /* Enough memory for all the columns */
  for (int i = 0; i < rows; i++) {
    array->array[i] = calloc(cols, sizeof(TYPE));
  }

  return array;
}

/* Frees a matrix */
void free_matrix(matrix *m) {
  /* Frees the elements inside the matrix */
  for (int i = 0; i < m->cols; i++) {
    free(m->array[i]);
  }
  free(m);
}

/* Debugging purposes only */
void print_matrix(const matrix *m) {
  for (int row = 0; row < m->rows; row++) {
    //printf("[");
    for (int col = 0; col < m->cols - 1; col++) {
      printf(FLAG" ", m->array[row][col]);
    }
    printf(FLAG, m->array[row][m->cols - 1]);
    printf("\n");
  }
  printf("\n");
}
