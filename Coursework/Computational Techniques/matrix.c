/*
 * matrix.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "matrix.h"
//#include "vector.h"

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
  matrix *m3 = create_matrix((TYPE**)malloc(sizeof(TYPE*) * m1->cols),m1->rows,m2->cols);

  TYPE sum = 0;

  /* Naive multiplication */
  for (int row=0; row<m1->rows; row++) {
    for (int col=0; col<m2->cols; col++) {
      for (int k=0; k<m1->cols; k++) {
        sum += m1->array[k][col] * m2->array[row][k];
      }
      m3->array[row][col] = sum;
      sum = 0;
    }
  }
  return m3;
}

/* Matrix transpose */
matrix* matrix_transpose(matrix* m) {
  /* Swap indices across the diagonal */
  /* Avoids malloc'ing more memory */
  int c = 1;
  for (int row = 0; row < m->rows; row++) {
    for (int col = c; col < m->cols; col++) {
      swap(m,row,col,col,row);
    }
    c++;
  }
  return m;
}

/* Decomposes the matrix A into QR */
QR* QRdecompose(matrix *A) {

  /* Using the Gram-Schmidt process */

  //QR* qr = malloc(sizeof(QR));

  //vector **Q = malloc(sizeof(vector*) * A->cols);

  //matrix *R = create_matrix((TYPE*) malloc(A->cols * A->rows * sizeof(TYPE)),
      //A->rows, A->cols);
  //qr->Q = Q;
  //qr->R = R;

  /* Obtain the orthonormal basis A */



  for (int i = 0; i < A->cols; i++) {

    //vector *q = vector_from_column(A,i);

    for (int j = 0; j <= i; j++) {

      //R->array[index(j,i,R->cols)] =

    }

   // R->array[index(i,i,A->cols)] = vector_length(q);
    //q = vector_div(q,vector_length(q));

    //Put in Q
    //Q[i] = q;

  }

  return NULL;//qr;
}

/* Creates a matrix and returns a pointer to the struct */
matrix* create_matrix(TYPE **m, int rows, int cols) {
  matrix *array = malloc(sizeof(matrix));

  /* Assuming the m is malloc'ed */
  array->array = m;

  for (int i=0; i<cols; i++) {
    array->array[i] = malloc(sizeof(TYPE) * cols);
  }

  array->rows = rows;
  array->cols = cols;
  return array;
}

/* Creates a matrix from a stack based array and returns a pointer to the struct */
matrix* create_matrix_from_array(int rows, int cols, TYPE m[][cols]) {
  matrix *array = malloc(sizeof(matrix));

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

  array->rows = rows;
  array->cols = cols;
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
void free_matrix(matrix *m) {
  /* Frees the elements inside the matrix */
  for (int i = 0; i<m->cols; i++) {
    free(m->array[i]);
  }
  free(m->array);
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
}
