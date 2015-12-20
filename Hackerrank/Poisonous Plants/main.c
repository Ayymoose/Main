/*
 * main.c
 *
 *  Created on: 20 Dec 2015
 *      Author: Ayman
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void printArray(int *array, int length) {
  printf("[");
  for (int i=0; i<length-1; i++) {
    printf("%d,",array[i]);
  }
  printf("%d]\n",array[length-1]);
}

/*
 * Problem: This current algorithm finds which plants are alive at the end but doesn't tell us how many days after all plants are still alive
 */

void checkPoisonousPlants(int *array, int length,int currentPlant, int nextPlant,int savedPlant,int poisonousPlants) {

  //Find the poisonous plants
  while (nextPlant<=length-1) {
    if (array[currentPlant] >= array[nextPlant]) {
      if (array[nextPlant] != 0) {
        if (savedPlant == 0) {
          currentPlant++;
        } else {
          currentPlant = nextPlant;
          savedPlant = 0;
        }
      } else {
        savedPlant = 1;
      }
      nextPlant++;
    } else {
      //We have found a poisonous plant which is nextPlant
      poisonousPlants++;
      // Kill the plant
      array[nextPlant] = 0;
      printf("Poisonous plant: %d\n",nextPlant+1);
      checkPoisonousPlants(array,length, currentPlant,nextPlant+1,savedPlant,poisonousPlants);
      printf("# Plants: %d\n",poisonousPlants);
    }
  }


}


int main() {


  int plants[] = {6,5,8,4,7,10,9};
  int arrayLength = sizeof(plants) / sizeof(plants[0]);
  checkPoisonousPlants(plants,arrayLength,0,1,0,0);
  printArray(plants,arrayLength);

 /* int n = 0;
  int *plants = malloc(sizeof(int) * n);
  scanf("%d",&n);

  for (int i=0; i<n; i++) {
    scanf("%d", &plants[i]);
  }*/
  return 0;
}

