/*
 * matrix.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "matrix.h"
#include "math.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define RANGE 25

/* Creates a symmetrix matrix out of array */
void symmetricise(matrix *array) {

  srand(time(NULL));

  /* Randomise only the upper or lower triangluar */

  int c = 1;
  for (int row = 0; row < array->rows; row++) {
    for (int col = c; col < array->cols; col++) {
      int r = (((RAND_MAX - rand()) % RANGE) + rand()) % RANGE;
      array->array[col][row] = r;
    }
    c++;
  }

  /* Makes array[row][col] = array[col][row] */
  /* Only to need to swap the upper or lower triangular */

  c = 1;
  for (int row = 0; row < array->rows; row++) {
    for (int col = c; col < array->cols; col++) {
      array->array[row][col] = array->array[col][row];
    }
    c++;
  }

}

/* Matrix multiplication (m1 * m2) */
matrix* matrix_multiply(matrix *m1, matrix *m2) {

  /* Remove for performance */
  assert(m1->cols == m2->rows);

  /* Result matrix */
  matrix *m3 = create_matrix(m1->rows,m2->cols);

  TYPE sum = 0;

  /* Naive multiplication */
  for (int row=0; row<m1->rows; row++) {
    for (int col=0; col<m2->cols; col++) {
      for (int k=0; k<m1->cols; k++) {
        sum +=  m1->array[row][k] * m2->array[k][col];
      }
      m3->array[row][col] = sum;
      sum = 0;
    }
  }
  return m3;
}

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void matrix_copy_column(matrix *msrc, int col1, matrix *mdst,int col2) {
  for (int i=0; i<msrc->rows; i++) {
    mdst->array[i][col2] = msrc->array[i][col1];
  }
}

/* Divides the matrix column c in m by k */
matrix* matrix_column_divide(matrix *m, int c, TYPE k) {
  for (int i=0; i<m->rows; i++) {
    m->array[i][c] /= k;
  }
  return m;
}

/* Multiplies the matrix column c in m by k */
matrix* matrix_column_multiply(matrix *m, int c, TYPE k) {
  for (int i=0; i<m->rows; i++) {
    m->array[i][c] *= k;
  }
  return m;
}

/* Subtracts m2's column c2 from m1's column c1 */
matrix* matrix_column_subtract(matrix *m1, int c1, matrix *m2, int c2) {
  for (int i=0; i<m1->rows; i++) {
      m1->array[i][c1] -= m2->array[i][c2];
  }
  return m1;
}

/* Returns the length of the vector column in m */
double vector_length(matrix *m,int column) {
  double length = 0;
  for (int row=0; row<m->rows; row++) {
    length += m->array[row][column] * m->array[row][column];
  }
  return sqrt(length);
}

/* Decomposes the matrix A into QR */
QR* QRdecompose(matrix *A) {

  /* Using the Gram-Schmidt process */

  QR* qr = malloc(sizeof(QR));
  matrix *Q = create_matrix(A->rows, A->cols);
  matrix *R = create_matrix(A->rows, A->cols);
  qr->Q = Q;
  qr->R = R;

  /* Temporary vector T and S used in calculations */
  matrix *T = create_matrix(A->rows, 1);
  matrix *S = create_matrix(A->rows, 1);

  for (int i = 0; i < A->cols; i++) {

    //Qi = Ui
    matrix_copy_column(A,i,Q,i);

    for (int j = 0; j <= i; j++) {

      //r[j,i] = Qj^T * Ui
      matrix_copy_column(Q,j,T,0);
      matrix_copy_column(A,i,S,0);

      TYPE r = 0;
      for (int k=0; k<A->rows; k++) {
        r += T->array[k][0] * S->array[k][0];
      }

      R->array[j][i] = r;

      //matrix *x = matrix_column_multiply(Q,j,r);

      //matrix_column_subtract(Q,i,x,j);

    }

    //r[i,i] = ||Qi||
    R->array[i][i] = vector_length(Q,i);
    //Qi = Qi/r[i,i]
    matrix_column_divide(Q,i,R->array[i][i]);

  }

  return qr;
}

/* Creates a matrix and returns a pointer to the struct */
matrix* create_matrix(int rows, int cols) {

  /* Allocate memory for the matrix struct */
  matrix *array = malloc(sizeof(matrix));

  array->rows = rows;
  array->cols = cols;

  /* Allocate enough memory for all the rows in the first matrix */
  array->array = calloc(rows, sizeof(TYPE*));

  /* Enough memory for all the columns */
  for (int i=0; i<rows; i++) {
    array->array[i] = calloc(cols,sizeof(TYPE));
  }

  return array;
}

/* Creates a matrix from a stack based array and returns a pointer to the struct */
matrix* create_matrix_from_array(int rows, int cols, TYPE m[][cols]) {

  /* Allocate memory for the matrix struct */
  matrix *array = malloc(sizeof(matrix));
  array->rows = rows;
  array->cols = cols;

  /* Allocate memory for the matrix */
  array->array = malloc(sizeof(TYPE*) * rows);

  /* Allocate memory for each array inside the matrix */
  for (int i=0; i<rows; i++) {
    array->array[i] = malloc(sizeof(TYPE) * cols);
  }

  /* Populate the matrix with m's values */
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      array->array[row][col] = m[row][col];
    }
  }

  return array;
}

/* Swaps the values at the matrix index */
/* swaps m[r1][c1] with m[r2][c2] */
void swap(matrix *m, int r1, int c1, int r2, int c2) {
  /* Remove assert for performance */
  assert(r1 >= 0 && c1 >= 0 && r1 < m->rows && c1 < m->cols);
  assert(r2 >= 0 && c2 >= 0 && r2 < m->rows && c2 < m->cols);

  TYPE temp = m->array[r1][c1];
  m->array[r1][c1] = m->array[r2][c2];
  m->array[r2][c2] = temp;
}

/* Frees a matrix */
/* BUG IN FREE MATRIX */
void free_matrix(matrix *m) {
  /* Frees the elements inside the matrix */
  for (int i = 0; i<m->cols; i++) {
    free(m->array[i]);
  }
  free(m);
}

/* Print the dimensions of a matrix (Debugging purposes only) */
void print_dimensions(matrix *m) {
  printf("%dx%d\n",m->rows,m->cols);
}

/* Debugging purposes only */
void print_matrix(matrix *m) {
  for (int row = 0; row < m->rows; row++) {
    printf("[");
    for (int col = 0; col < m->cols - 1; col++) {
      printf(FLAG", ", m->array[row][col]);
    }
    printf(FLAG, m->array[row][m->cols-1]);
    printf("]\n");
  }
  printf("\n");
}
