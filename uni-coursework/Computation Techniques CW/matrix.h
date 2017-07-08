/*
 * matrix.h
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "defines.h"
#include <stdbool.h>

/* Change here to adjust matrix size*/
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* Smaller value of epsilon yields more accurate results for the eigenvalues of A */
#define EPSILON 0.000001

typedef struct {
  TYPE **array; /* Pointer to an array of type TYPE */
  int rows; /* Number of rows */
  int cols; /* Number of columns */
} matrix;

/* Creates a random symmetrix matrix */
matrix* symmetricise(matrix *m);

/* Creates a matrix and returns a pointer to the struct */
matrix* matrix_create(int rows, int cols);

/* Checks if a matrix is diagonal */
bool matrix_is_diagonal(const matrix *m);

/* Matrix multiplication m3 = (m1 * m2) */
matrix* matrix_multiply(const matrix *m1, const matrix *m2, matrix *m3);

/* Adds two (square) matrices together m3 = m1 + m2 */
matrix* matrix_add(const matrix *m1, const matrix *m2, matrix *m3);

/* Divides the matrix column c in m by k */
matrix* matrix_column_divide(matrix *m, int c, TYPE k);

/* Multiplies the matrix column c in m by k */
matrix* matrix_column_multiply(matrix *m, int c, TYPE k);

/* Subtracts m2's column c2 from m1's column c1 */
matrix* matrix_column_subtract(matrix *m1, int c1, const matrix *m2, int c2);

/* Copies a matrix column from msrc at column col1 to mdst at column col2 */
void matrix_copy_column(const matrix *msrc, int col1, matrix *mdst, int col2);

/* Returns the length of the vector column in m */
double vector_length(const matrix *m, int column);

/* Frees a matrix */
void free_matrix(matrix *m);

/* Decomposes the matrix A into QR */
void QRdecompose(const matrix *A, matrix *Q, matrix *R);

/* Print a matrix (Debugging purposes only) */
void print_matrix(const matrix *m);

#endif /* MATRIX_H_ */
