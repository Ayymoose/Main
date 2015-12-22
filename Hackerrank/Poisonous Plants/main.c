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


//Bug in this code
//Does not check if array[currentPlant] is 0 before comparison
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
      printArray(array,length);
      plantsAlive(array,length, currentPlant,nextPlant+1,savedPlant,poisonousPlants);
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

  //Easier to assign currentPlant to nextPlant then have nextPlant++

  while (nextPlant <= length - 1) {
    if (deadPlantPesticide > 0) {
      if (array[nextPlant] != DEAD) {
        if (deadPlantPesticide >= array[nextPlant]) {
          deadPlantPesticide = 0;
        } else {
          killPlant(array, &poisonousPlants, &deadPlantPesticide, nextPlant);
        }
        currentPlant++;
      }
      nextPlant++;
    } else {
      if (array[currentPlant] == DEAD || array[nextPlant] == DEAD) {
        currentPlant += (array[currentPlant] == DEAD ? 1 : 0);
        nextPlant += (array[nextPlant] == DEAD ? 1 : 0);
      } else {
        if (array[currentPlant] < array[nextPlant]) {
          killPlant(array, &poisonousPlants, &deadPlantPesticide, nextPlant);
        }
        currentPlant=nextPlant++;
      }
    }
  }
  return poisonousPlants;
}


int main() {


  /*
   * 17
     20 5 6 15 2 2 17 2 11 5 14 5 10 9 19 12 5
     Answer = 4
   */

 // int plants[] = {20 ,5, 6, 15, 2 ,2 ,17 ,2 ,11, 5 ,14 ,5 ,10 ,9 ,19 ,12 ,5};

  /*
   * Day 1 (7 dead) 20 5 - - 2 2 - 2 - 5 - 5 - 9 - 12 5
   * Day 2 (3 dead) 20 5 _ _ 2 2 _ 2 _ 5 _ 5 _ 9 _ 12 5
   * Day 3 (4 dead) 20 5 _ _ 2 2 _ 2 _ _ _ _ _ _ _ _ 5
   * Day 4 20 5 _ _ 2 2 _ 2 _ _ _ _ _ _ _ _ _
   *
   */

  /*int days = 0;
  int poisonousPlants = checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]));
  printf("%d\n",poisonousPlants);
  poisonousPlants = checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]));
  printf("%d\n",poisonousPlants);
  poisonousPlants = checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]));
  printf("%d\n",poisonousPlants);
  poisonousPlants = checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]));
  printf("%d\n",poisonousPlants);
  poisonousPlants = checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]));
  printf("%d\n",poisonousPlants);*/

  /*while(checkPoisonousPlants(plants,sizeof(plants)/sizeof(plants[0]))) {
    days++;
  }*/


  //plantsAlive(plants,sizeof(plants)/sizeof(plants[0]),0,1,0,0);


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

