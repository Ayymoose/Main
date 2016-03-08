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

  double d1=1,d2=0;
  while (fabs(d1-d2) > EPSILON) {
    QRdecompose(A,Q,R);
    d1 = A->array[0][0];
    matrix_multiply(R,Q,A);
    d2 = A->array[0][0];
  }

  //print_matrix(A);
  if (write_matrices_to_file(A,Q,"results.txt")) {
    printf("Success\n");
  }

  free_matrix(A);
  free_matrix(Q);
  free_matrix(R);

  return 0;
}

