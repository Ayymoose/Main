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
bool write_matrices_to_file(const matrix *eigenvalues,
    const matrix *eigenvectors, const char* filename) {

  /* Write to a new file */
  FILE *file = fopen(filename, "w");

  if (file == NULL) {
    printf("Error opening file '%s'\n", filename);
    exit(1);
  }

  /* Write the eigenvalues and eigenvectors */
  for (int i = 0, k = 0; i < eigenvalues->cols; i++) {
    fprintf(file, "Eigenvalue "FLAG" and Eigenvector [",
        eigenvalues->array[i][i]);
    for (int j = 0; j < eigenvectors->rows - 1; j++) {
      fprintf(file, FLAG", ", eigenvectors->array[j][k]);
    }
    fprintf(file, FLAG"]\n", eigenvectors->array[eigenvectors->rows - 1][k]);
    k++;
  }

  fclose(file);
  return true;
}

int main(int argc, const char **argv) {

  //TYPE a[2][2] = {{ 0,1 }, { -2,-3}};
  // matrix *A = matrix_create_from_array(2,2,a);//*/

  matrix *A = matrix_create(MATRIX_ROWS, MATRIX_COLS);
  symmetricise(A);
  printf("A\n");
  print_matrix(A);

  /* Matrices Q and R */
  matrix *Q = matrix_create(MATRIX_ROWS, MATRIX_COLS);
  matrix *R = matrix_create(MATRIX_ROWS, MATRIX_COLS);

  /* Identity and accumulator matrix for Q eigenvector calculation  */
  matrix *I = matrix_create_diagonal(MATRIX_ROWS, MATRIX_COLS, 1);
  matrix *Accumulator = matrix_create(MATRIX_ROWS, MATRIX_COLS);

  /* Positive and negative shift matrices */
  /*TYPE sigma = A->array[A->rows - 1][A->rows - 1];
  matrix *neg_shift_matrix = matrix_create_diagonal(MATRIX_ROWS, MATRIX_COLS,
      -sigma);
  matrix *pos_shift_matrix = matrix_create_diagonal(MATRIX_ROWS, MATRIX_COLS,
      sigma);*/

  double d1 = 1, d2 = 0;

  while (fabs(d1 - d2) > EPSILON) {

    d1 = A->array[0][0];

    /* Subtract shift matrix from A */
    //matrix_add(A, neg_shift_matrix, A);

    /* A = QR */
    QRdecompose(A, Q, R);

    /* Multiply successive Q matrices to obtain eigenvectors */
    matrix_multiply(Q, I, Accumulator);

    /* Swap the pointers */
    matrix *temp = I;
    I = Accumulator;
    Accumulator = temp;

    /* A = RQ */
    matrix_multiply(R, Q, A);

    /* Add shift matrix to A */
    //matrix_add(A, pos_shift_matrix, A);

    d2 = A->array[0][0];
  }

  printf("Q\n");
  print_matrix(Q);
  printf("R\n");
  print_matrix(R);

  const char *filename = "results.txt";
  if (write_matrices_to_file(A, Accumulator, filename)) {
    printf("Matrices successfully written to file '%s'\n", filename);
  } else {
    printf("Error occured writing matrices to file '%s'\n", filename);
  }

  free_matrix(A);
  free_matrix(Q);
  free_matrix(R);
  free_matrix(I);
  free_matrix(Accumulator);
  //free_matrix(neg_shift_matrix);
  //free_matrix(pos_shift_matrix);

  return 0;
}
