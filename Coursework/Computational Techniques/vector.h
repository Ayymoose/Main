/*
 * vector.h
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "math.h"
#include "defines.h"

typedef struct {
  TYPE *vector; /* An arbitrary sized vector */
  int size;     /* That has size elements */
} vector;

#include "matrix.h"

/* Creates an arbitrary sized vector denoted by size elements */
vector* create_vector(TYPE *array, int size);

/* Create a vector from an m column */
vector* vector_from_column(matrix *array, int column);

/* Returns the length of a vector */
double vector_length(vector *vec);

/* Normalises a vector */
vector* normalise(vector *vec);

/* Subtracts two vectors (v1 - v2) */
vector* vector_sub(vector *v1, vector *v2);

/* Multiplies v by k (constant) */
vector* vector_mul(vector *v, TYPE k);

/* Divides v by k (constant) */
vector* vector_div(vector *v, TYPE k);

/* Returns the dot product of v1 and v2 */
TYPE dot(vector *v1, vector *v2);

/* Print a vector (Debugging purposes only) */
void print_vector(vector* vec);

#endif /* VECTOR_H_ */
