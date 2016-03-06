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
  TYPE *array;    /* Pointer to an array of type TYPE */
  int rows;       /* Number of rows */
  int cols;       /* Number of columns */
} matrix;


#include "vector.h"



typedef struct {
  vector **Q;  /* Orthogonal matrix Q */
  matrix *R;  /* Right upper triangular matrix R */
} QR;

/* Creates a random symmetric matrix A from arry passed in */
void symmetricise(matrix *matrix);

/* Creates a 2D array and returns a pointer to the struct */
matrix* create_matrix(TYPE *matrix, int rows, int cols);

/* Matrix multiplication */
matrix* matrix_multiply(matrix *m1, matrix *m2);

/* Matrix transpose */
matrix* transpose(matrix* m);

// DONT FORGET TO CALL FREE

/* Decomposes the matrix A into QR (A = QR) */
QR* QRdecompose(matrix *A);

/* Print a matrix (Debugging purposes only) */
void print_matrix(matrix *matrix);

#endif /* MATRIX_H_ */
