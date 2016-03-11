/*
 * main.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "matrix.h"
#include "defines.h"

/* Writes the matrix contained eigenvalues and eigenvectors to file filename*/
bool write_matrices_to_file(const matrix *eigenvalues, const matrix *eigenvectors, const char* filename) {

  /* Write to a new file */
  FILE *file = fopen(filename,"w");

  if (file == NULL) {
    printf("Error opening file '%s'\n", filename);
    exit(1);
  }

  /* Write the eigenvalues and eigenvectors */
  for (int i=0,k=0; i<eigenvalues->cols; i++) {
    fprintf(file, "Eigenvalue "FLAG" and Eigenvector [",eigenvalues->array[i][i]);
    for (int j=0; j<eigenvectors->rows-1; j++) {
      fprintf(file, FLAG", ", eigenvectors->array[j][k]);
    }
    fprintf(file, FLAG"]\n", eigenvectors->array[eigenvectors->rows-1][k]);
    k++;
  }

  fclose(file);
  return true;
}

int main(int argc, const char **argv) {

  //TYPE a[3][3] = { { 12, -51, 4 }, { 6, 167, -68 }, { -4, 24, -41 } };

  TYPE a[2][2] = {{ 7,2 }, { 2,4}};

  matrix *A = matrix_create_from_array(2,2,a);
  matrix *Q = matrix_create(2,2);
  matrix *R = matrix_create(2,2);

  matrix *I = matrix_create_diagonal(2,2,1);
  matrix *Accumulator = matrix_create(2,2);

  TYPE sigma = 4;
  matrix *neg = matrix_create_diagonal(2,2,-sigma);
  matrix *pos = matrix_create_diagonal(2,2,sigma);

  double d1=1,d2=0;
  int iterations = 0;

  while (fabs(d1-d2) > EPSILON) {
    QRdecompose(A,Q,R);


    matrix_add(A,neg,A);


    d1 = A->array[0][0];
    matrix_multiply(Q,I,Accumulator);
    /* Swap the pointers */
    matrix *temp = I;
    I = Accumulator;
    Accumulator = temp;

    matrix_multiply(R,Q,A);
    matrix_add(A,pos,A);

    print_matrix(A);
       break;

    d2 = A->array[0][0];
    iterations++;
  }

 /* printf("Iterations %d\n", iterations);

  if (write_matrices_to_file(A,Accumulator,"results.txt")) {
    printf("Matrices successfully written to file \n");
  }*/

  free_matrix(A);
  free_matrix(Q);
  free_matrix(R);
  free_matrix(I);
  free_matrix(Accumulator);

  return 0;
}

