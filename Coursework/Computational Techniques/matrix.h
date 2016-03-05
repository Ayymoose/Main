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
  TYPE *array;  /* Pointer to a double */
  int rows;       /* Number of rows */
  int cols;       /* Number of columns */
} array2D;

typedef struct {
  array2D *Q;  /* Orthogonal matrix Q */
  array2D *R;  /* Right upper triangular matrix R */
} QR;

/* Creates a random symmetric matrix A from arry passed in */
void symmetricise(array2D *array);

/* Creates a 2D array and returns a pointer to the struct */
array2D* create2DArray(TYPE *array, int rows, int cols);

// DONT FORGET TO CALL FREE

/* Decomposes the matrix A into QR (A = QR) */
QR* QRdecompose(array2D *A);

/* Print a matrix (Debugging purposes only) */
void printMatrix(array2D *array);

#endif /* MATRIX_H_ */
