/*
 * main.c
 *
 *  Created on: 20 Dec 2015
 *      Author: Ayman
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n;
    scanf("%d",&n);
    int *arr = malloc(sizeof(int) * n);
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[arr_i]);
    }
    for (int i=n-1; i>=0; i--) {
      printf("%d ",arr[i]);
    }
    free(arr);
    return 0;
}
