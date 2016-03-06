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

#define index(ROW,COL,NUM_COLS) ((ROW * NUM_COLS) + COL)

/* Creates an arbitrary sized vector denoted by size elements */
vector* createVector(TYPE *array, int size) {
  assert(size != 0);
  vector* vec = malloc(sizeof(vector));
  vec->vector = array;
  vec->size = size;
  vec->type = sizeof(TYPE);
  return vec;
}

/* Create a vector from an array column */
vector* vectorFromColumn(matrix *array,int column) {

  assert(column < array->rows);

  vector* vec = malloc(sizeof(vector));
  vec->size = array->rows;
  vec->vector = malloc(sizeof(vec->size * vec->type));

  for (int row=0; row<vec->size; row++) {
    vec->vector[row] = array->array[index(row,column,vec->size)];
  }
  return vec;
}

/* Returns the length of a vector */
double vectorLength(vector *vec) {
  double length = 0;
  for (int i=0; i<vec->size; i++) {
    length += vec->vector[i] * vec->vector[i];
  }
  return sqrt(length);
}

/* Normalises a vector */
vector* normalise(vector *vec) {
  double length = vectorLength(vec);
  for (int i=0; i<vec->size; i++) {
    vec->vector[i] /= length;
  }
  return vec;
}

/* Subtracts two vectors */
vector* sub(vector *v1, vector *v2) {
  for (int i=0; i<v1->size; i++) {
    v1->vector[i] -= v2->vector[i];
  }
  return v1;
}

/* Multiplies v by k */
vector* mul(vector *v, TYPE k) {
  for (int i=0; i<v->size; i++) {
    v->vector[i] *= k;
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
void printVector(vector* vec) {
  for (int i=0; i<vec->size; i++) {
    printf("["FLAG"]\n", vec->vector[i]);
  }
}
