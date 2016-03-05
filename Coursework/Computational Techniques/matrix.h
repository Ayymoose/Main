/*
 * matrix.h
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
  double *array;  /* Pointer to a double */
  int rows;       /* Number of rows */
  int cols;       /* Number of columns */
} array2D;

/* Creates a random symmetric matrix A from arry passed in */
void symmetricise(array2D *array);

/* Creates a 2D array and returns a pointer to the struct */
array2D* create2DArray(double *array, int rows, int cols);

// DONT FORGET TO CALL FREE

/* Print a matrix (Debugging purposes only) */
void printMatrix(array2D *array);

#endif /* MATRIX_H_ */
