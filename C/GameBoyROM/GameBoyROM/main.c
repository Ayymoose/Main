#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

//Header files 
#include "cartridge.h"

/*

  GameBoy Cartridge (ROM) information
  Load a ROM and it will display the details of the ROM

*/


int main(int argc, char** argv) {

  //Command line: GameBoyROM.exe rom.gb
  const char *fileName = argv[1];
  gameBoyROM *rom;
  unsigned char *romData;


    //We only need to read the header of the file but loadROM loads the entire file into memory
    //I should create another function; loadROMHeader() which only loads the header
    romData = loadROM(fopen(fileName, "r")); 
    if (romData) {
      rom = parseROM(romData);
      char** romDisplay = displayROM(rom);
	  //"Game title: \t\t%s\nLicense: \t\t%s\nFeatures: \t\t%s\nCartridge Type: \t%s\nROM Size: \t\t%s\nRAM Size: \t\t%s\nDestination Code: \t%s\nLicensee (Old): \t%s\n"
      printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", displayROM(rom)[0],
        romDisplay[1],
        romDisplay[2],
        romDisplay[3],
        romDisplay[4],
        romDisplay[5],
        romDisplay[6],
        romDisplay[7]);
      //Free allocated memory

      free(romData);
      free(rom);
     // getchar();
    }

  return 0;
}

/*POKEMON RED
Nintendo
Super GameBoy functions
MBC3 + RAM + BATTERY
1MB
32kB
Non - Japanese
Unknown*/