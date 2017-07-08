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
    fprintf(file, "Eigenvalue "FLAG" and Eigenvector "BRACKET_OPEN,
        eigenvalues->array[i][i]);
    for (int j = 0; j < eigenvectors->rows - 1; j++) {
      fprintf(file, FLAG", ", eigenvectors->array[j][k]);
    }
    fprintf(file, FLAG BRACKET_CLOSE"\n", eigenvectors->array[eigenvectors->rows - 1][k]);
    k++;
  }

  fclose(file);
  return true;
}

int main(int argc, const char **argv) {

  matrix *A = matrix_create(MATRIX_ROWS, MATRIX_COLS);
  symmetricise(A);

  /* Matrices Q and R */
  matrix *Q = matrix_create(MATRIX_ROWS, MATRIX_COLS);
  matrix *R = matrix_create(MATRIX_ROWS, MATRIX_COLS);

  /* Identity and accumulator matrix for Q eigenvector calculation  */
  matrix *Qnext = matrix_create(MATRIX_ROWS, MATRIX_COLS);
  matrix *Qacc = matrix_create(MATRIX_ROWS, MATRIX_COLS);

  /* Print matrix A */
  printf("A\n");
  print_matrix(A);

  /* A = QR */
  QRdecompose(A, Q, R);

  /* Print matrix Q */
  printf("Q\n");
  print_matrix(Q);

  /* Print matrix R */
  printf("R\n");
  print_matrix(R);

  /* A = RQ */
  matrix_multiply(R, Q, A);

  matrix *Qprev = Q;

  int iterations = 0;

  while (!matrix_is_diagonal(A)) {

    /* Obtain new Q and R */
    QRdecompose(A, Qnext, R);

    /* A = RQ */
    matrix_multiply(R, Qnext, A);

    /* Multiply successive Q matrices to obtain eigenvectors */
    matrix_multiply(Qprev, Qnext, Qacc);

    /* Swap the Qacc with Qprev */
    matrix *temp = Qprev;
    Qprev = Qacc;
    Qacc = temp;

    iterations++;

  }

  printf("Iterations %d\nEPSILON %f\n",iterations,EPSILON);

  const char *filename = "results.txt";
  if (write_matrices_to_file(A, Qacc, filename)) {
    printf("Matrices successfully written to file '%s'\n", filename);
  } else {
    printf("Error occured writing matrices to file '%s'\n", filename);
  }

  free_matrix(A);
  free_matrix(Q);
  free_matrix(R);
  free_matrix(Qacc);
  free_matrix(Qnext);
  return 0;
}
