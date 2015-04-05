#pragma once
#include <stdio.h>

#define MAX_TITLE_LENGTH 15 //Or 16??

//General structure of the ROM header for gameboy ROMs
typedef struct romHeader {
  char title[MAX_TITLE_LENGTH]; /* Title of the game in upper case ASCII */
  unsigned char licenceHigh;    /* Licensee (High nibble) */
  unsigned char licenseLow;     /* Licensee (Low nibble) */
  unsigned char feature;        /* SGB Indicator */
  unsigned char cartridgeType;  /* Cartridge type */
  unsigned char romSize;        /* ROM Size */
  unsigned char ramSize;        /* RAM Size */
  unsigned char destCode;       /* Destination code */
  unsigned char licenseeCode;   /* Licensee code (old) */
                                //Omitted three other fields we don't care about (checkSum + complement + mask ROM Version)
} gameBoyROM;

//Load a ROM file and return a pointer to the memory
unsigned char* loadROM(FILE* rom);

//Loads the header file of a ROM 
//unsigned char* loadROMHeader(FILE* rom);

//Parses a gameboy ROM file (pointer to the data) and returns a pointer to the struct with infromation filled in
gameBoyROM* parseROM(unsigned char* rom);

//Returns an array of strings with the fields of the structure filled out with the correct information
char** displayROM(gameBoyROM* ROM);