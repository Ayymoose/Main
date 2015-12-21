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

#define DEAD 0
#define NONE 0

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

void plantsAlive(int *array, int length,int currentPlant, int nextPlant,int savedPlant,int poisonousPlants) {

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
      plantsAlive(array,length, currentPlant,nextPlant+1,savedPlant,poisonousPlants);
      printf("# Plants: %d\n",poisonousPlants);
    }
  }


}

// Kills a plant
void killPlant(int *array, int *poisonousPlants, int *deadPlantPesticide, int nextPlant) {
  //We've come across a poisonous plant which is nextPlant
  (*poisonousPlants)++;
  *deadPlantPesticide = array[nextPlant];
  //Mark as dead
  array[nextPlant] = DEAD;
}

// Does 1 pass and checks how many poisonous plants died
int checkPoisonousPlants(int *array, int length) {

  int deadPlantPesticide = NONE;
  int currentPlant = 0;
  int nextPlant = 1;
  int poisonousPlants = NONE;

  while (nextPlant <= length - 1) {
    if (deadPlantPesticide > 0) {
      if (deadPlantPesticide > array[nextPlant]) {
        deadPlantPesticide = 0;
      } else {
        killPlant(array, &poisonousPlants, &deadPlantPesticide, nextPlant);
      }
      currentPlant++;
      nextPlant++;
    } else {
      if (array[currentPlant] == DEAD || array[nextPlant] == DEAD) {
        currentPlant += (array[currentPlant] == DEAD ? 1 : 0);
        nextPlant += (array[nextPlant] == DEAD ? 1 : 0);
      } else {
        if (array[currentPlant] < array[nextPlant]) {
          killPlant(array, &poisonousPlants, &deadPlantPesticide, nextPlant);
        }
        currentPlant++;
        nextPlant++;
      }
    }
  }
  return poisonousPlants;
}


int main() {


  int n = 0;
  scanf("%d",&n);
  int *plants = malloc(sizeof(int) * n);
  for (int i=0; i<n; i++) {
    scanf("%d", &plants[i]);
  }
  int days = 0;
  while(checkPoisonousPlants(plants,n)) {
    days++;
  }
  printf("%d\n",days);
  return 0;
}

