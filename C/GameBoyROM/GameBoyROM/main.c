#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

//Header files 
#include "cartridge.h"

/*

  GameBoy Cartridge (ROM) information
  Load a ROM and it will display the details of the ROM

*/

#define EXPECTED_ARGUMENTS 1
#define VERSION 1
#define TITLE "Gameboy ROM information"
#define AUTHOR "Moose"

#define MAX_ITEMS 8

int main(int argc, char** argv) {

  //Command line: GameBoyROM.exe <name_of_file>
  printf("%s version %d\nCreated by %s\n", TITLE, VERSION, AUTHOR);
  const char* fileName = argv[1];
  gameBoyROM* rom;
  unsigned char* romData;

  switch (argc)
  {
  case EXPECTED_ARGUMENTS + 1:
    //We only need to read the header of the file but loadROM loads the entire file into memory
    //I should create another function; loadROMHeader() which only loads the header
    romData = loadROM(fopen(fileName, "r")); 
    if (romData) {
      printf("Reading %s\n", fileName);
      printf("---------------------------------------\n");
      rom = parseROM(romData);
      char** romDisplay = displayROM(rom);

      printf(" Game title: \t\t%s\n License: \t\t%s\n Features: \t\t%s\n Cartridge Type: \t%s\n ROM Size: \t\t%s\n RAM Size: \t\t%s\n Destination Code: \t%s\n Licensee (Old): \t%s\n", displayROM(rom)[0],
        romDisplay[1],
        romDisplay[2],
        romDisplay[3],
        romDisplay[4],
        romDisplay[5],
        romDisplay[6],
        romDisplay[7]);

      printf("---------------------------------------\n");
      printf("Press enter to exit...");

      //Free allocated memory
      free(romData);
      free(rom);
      getchar();
    }
    break;
  default:
    //Exit
    break;
  }
  return 0;
}