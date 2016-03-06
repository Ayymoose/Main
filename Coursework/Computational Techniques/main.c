/*
 * main.c
 *
 *  Created on: 5 Mar 2016
 *      Author: Ayman
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include "defines.h"

/*
 int main(){
  int a[5][5],b[5][5],c[5][5],i,j,k,sum=0,m,n,o,p;
  printf("\nEnter the row and column of first matrix");
  scanf("%d %d",&m,&n);
  printf("\nEnter the row and column of second matrix");
  scanf("%d %d",&o,&p);
  if(n!=o){
      printf("Matrix mutiplication is not possible");
      printf("\nColumn of first matrix must be same as row of second matrix");
  }
  else{
      printf("\nEnter the First matrix->");
      for(i=0;i<m;i++)
      for(j=0;j<n;j++)
           scanf("%d",&a[i][j]);
      printf("\nEnter the Second matrix->");
      for(i=0;i<o;i++)
      for(j=0;j<p;j++)
           scanf("%d",&b[i][j]);
      printf("\nThe First matrix is\n");
      for(i=0;i<m;i++){
      printf("\n");
      for(j=0;j<n;j++){
           printf("%d\t",a[i][j]);
      }
      }
      printf("\nThe Second matrix is\n");
      for(i=0;i<o;i++){
      printf("\n");
      for(j=0;j<p;j++){
           printf("%d\t",b[i][j]);
      }
      }
      for(i=0;i<m;i++)
      for(j=0;j<p;j++)
           c[i][j]=0;
      for(i=0;i<m;i++){ //row of first matrix
      for(j=0;j<p;j++){  //column of second matrix
           sum=0;
           for(k=0;k<n;k++)
               sum=sum+a[i][k]*b[k][j];
           c[i][j]=sum;
      }
      }
  }
  printf("\nThe multiplication of two matrix is\n");
  for(i=0;i<m;i++){
      printf("\n");
      for(j=0;j<p;j++){
           printf("%d\t",c[i][j]);
      }
  }
  return 0;
}*/

int main(int argc, const char **argv) {



  int a[3][1] =
  {
      {1},
      {3},
      {4},
  };

  int b[1][4] =
  {
        {1,2,3,4},
  };

  //matrix *ary = create_matrix(b,1,3);
  //matrix *c = transpose(ary);

  matrix *m1 = create_matrix_from_array(3,1,a);
  matrix *m2 = create_matrix_from_array(1,4,b);
  matrix *m3 = matrix_multiply(m1,m2);

  print_matrix(m3);

  free_matrix(m1);
  free_matrix(m2);
  free_matrix(m3);


  return 0;
}

/*
 *
 *
1 2 3 4
3 6 9 12
4 8 12 16
 *
 *
 */
