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

typedef struct {
  matrix *Q;  /* Orthogonal matrix Q */
  matrix *R;  /* Right upper triangular matrix R */
} QR;

/* Creates a random symmetric matrix A from arry passed in */
void symmetricise(matrix *m);

/* Creates a matrix and returns a pointer to the struct */
matrix* create_matrix(int rows, int cols);

/* Creates a matrix from a stack based array and returns a pointer to the struct */
matrix* create_matrix_from_array(int rows, int cols, TYPE m[][cols]);

/* Matrix multiplication */
matrix* matrix_multiply(matrix *m1, matrix *m2);

/* Tranposes a column matrix into a row matrix */
matrix* matrix_transpose_column(matrix *m);

/* Divides the matrix column c in m by k */
matrix* matrix_column_divide(matrix *m, int c, TYPE k);

/* Multiplies the matrix column c in m by k */
matrix* matrix_column_multiply(matrix *m, int c, TYPE k);

/* Subtracts m2's column c2 from m1's column c1 */
matrix* matrix_column_subtract(matrix *m1, int c1, matrix *m2, int c2);


/* Swaps the values at the matrix index */
/* swaps m[r1][c1] with m[r2][c2] */
void swap(matrix *m, int r1, int c1, int r2, int c2);

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void matrix_copy_column(matrix *msrc, int col1, matrix *mdst,int col2);

/* Returns the length of the vector column in m */
double vector_length(matrix *m, int column);

/* Frees a matrix */
void free_matrix(matrix *m);

/* Decomposes the matrix A into QR (A = QR) */
QR* QRdecompose(matrix *A);

/* Print the dimensions of a matrix (Debugging purposes only) */
void print_dimensions(matrix *m);

/* Print a matrix (Debugging purposes only) */
void print_matrix(matrix *m);

#endif /* MATRIX_H_ */
