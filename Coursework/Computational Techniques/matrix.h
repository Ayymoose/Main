/*
 * matrix.h
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */


#ifndef MATRIX_H_
#define MATRIX_H_

#include "defines.h"

typedef struct {
  TYPE **array;    /* Pointer to an array of type TYPE */
  int rows;       /* Number of rows */
  int cols;       /* Number of columns */
} matrix;


//#include "vector.h"

typedef struct {
  matrix *Q;  /* Orthogonal matrix Q */
  matrix *R;  /* Right upper triangular matrix R */
} QR;

/* Creates a random symmetric matrix A from arry passed in */
void symmetricise(matrix *m);

/* Creates a matrix and returns a pointer to the struct */
matrix* create_matrix(TYPE **m, int rows, int cols);

/* Creates a matrix from a stack based array and returns a pointer to the struct */
matrix* create_matrix_from_array(int rows, int cols, TYPE m[][cols]);

/* Matrix multiplication */
matrix* matrix_multiply(matrix *m1, matrix *m2);

/* Matrix transpose */
matrix* matrix_transpose(matrix *m);

/* Swaps the values at the matrix index */
/* swaps m[r1][c1] with m[r2][c2] */
void swap(matrix *m, int r1, int c1, int r2, int c2);

/* Frees a matrix */
void free_matrix(matrix *m);

/* Decomposes the matrix A into QR (A = QR) */
QR* QRdecompose(matrix *A);

/* Print a matrix (Debugging purposes only) */
void print_matrix(matrix *);

#endif /* MATRIX_H_ */
