/*
 * vector.h
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include "math.h"
#include "defines.h"
#include "matrix.h"

#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct {
  TYPE *vector; /* An arbitrary sized vector */
  int size;     /* That has size elements */
  TYPE type;    /* malloc() purposes */
} vector;

/* Creates an arbitrary sized vector denoted by size elements */
vector* createVector(TYPE *array, int size);

/* Create a vector from an array column */
vector* vectorFromColumn(array2D *array, int column);

/* Returns the length of a vector */
double vectorLength(vector *vec);

/* Normalises a vector */
void normalise(vector *vec);

/* Returns the dot product of v1 and v2 */
TYPE dot(vector *v1, vector *v2);

/* Print a vector (Debugging purposes only) */
void printVector(vector* vec);

#endif /* VECTOR_H_ */
