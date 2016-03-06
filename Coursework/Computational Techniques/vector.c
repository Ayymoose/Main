/*
 * vector.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */


#include "vector.h"
#include "matrix.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* Creates an arbitrary sized vector denoted by size elements */
vector* create_vector(TYPE *array, int size) {
  assert(size != 0);
  vector *vec = malloc(sizeof(vector));
  vec->vector = array;
  vec->size = size;
  return vec;
}

/* Create a vector from an array column */
vector* vector_from_column(matrix *array,int column) {

  assert(column < array->rows);

  vector *vec = malloc(sizeof(vector));
  vec->size = array->rows;
  vec->vector = malloc(sizeof(vec->size * sizeof(TYPE)));

  for (int row=0; row<vec->size; row++) {
    vec->vector[row] = array->array[index(row,column,vec->size)];
  }
  return vec;
}

/* Returns the length of a vector */
double vector_length(vector *vec) {
  double length = 0;
  for (int i=0; i<vec->size; i++) {
    length += vec->vector[i] * vec->vector[i];
  }
  return sqrt(length);
}

/* Normalises a vector */
vector* normalise(vector *vec) {
  double length = vector_length(vec);
  for (int i=0; i<vec->size; i++) {
    vec->vector[i] /= length;
  }
  return vec;
}

/* Subtracts two vectors */
vector* vector_sub(vector *v1, vector *v2) {
  for (int i=0; i<v1->size; i++) {
    v1->vector[i] -= v2->vector[i];
  }
  return v1;
}

/* Multiplies v by k */
vector* vector_mul(vector *v, TYPE k) {
  for (int i=0; i<v->size; i++) {
    v->vector[i] *= k;
  }
  return v;
}

/* Divides v by k */
vector* vector_div(vector *v, TYPE k) {
  for (int i=0; i<v->size; i++) {
    v->vector[i] /= k;
  }
  return v;
}

/* Returns the dot product of v1 and v2 */
TYPE dot(vector *v1, vector *v2) {
  /* Remove assertion for performance */
  assert(v1->size == v2->size);

  TYPE result = 0;
  for (int i=0; i<v1->size; i++) {
    result += v1->vector[i] * v2->vector[i];
  }
  return result;
}

/* Print a vector (Debugging purposes only) */
void print_vector(vector* vec) {
  for (int i=0; i<vec->size; i++) {
    printf("["FLAG"]\n", vec->vector[i]);
  }
}
