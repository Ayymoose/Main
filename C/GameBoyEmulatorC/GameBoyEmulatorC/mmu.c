//Memory Management Unit
//Handles all memory related (things)

//Include file header here
#include <stdlib.h>
#include <string.h>
#include "mmu.h"
//#include "z80.c"

typedef unsigned char byte;
typedef unsigned short word;

//

//Memory map for the Z80
struct RAM {
  
  //Main ROM which is split into sub sections below
  /* 32kB of ROM [0x0000 - 0x7FFF] */

  //Although the size of the rom is 32kB, we can load the entire ROM into memory on a PC
  byte* rom;

  //ROM bank 0 (16kB) contains the cartridge program
  /* [0x0000 - 0x3FFF] Cartridge program in available in memory */

  //Which includes
    /* [0x0000 - 0x00FF] 256 bytes for the BIOS             */
    /* [0x0100 - 0x014F] 80 bytes for cartridge information */
  //

  byte bios[BIOS_SIZE];

  /* 8kB of Graphics RAM [0x8000 - 0x9FFF] */
  byte vram[VRAM_SIZE];

  /* 8kB of External (Cartridge) RAM [0xA000 - 0xBFFF] */
  byte eram[EXTERNAL_RAM_SIZE];

  /* 8kB of Internal RAM [0xC000 - 0xDFFF] */
  //Also has a shadow copy where if you write in this address it will also be written in [0xE000 - 0xFDFF] 

  byte iram[INTERNAL_RAM_SIZE];

  /* 128 bytes of zero page RAM (as described by Nazaar) [0xFF80 - 0xFFFF] */
  byte zram[ZERO_PAGE_RAM_SIZE];

  /*
  
  Also need OAM which the GPU will handle
  0xFF00 - 0xFF7F seems to be unhandled but on the documentation manual, it also lists 0xFEA0 - 0xFF00 as unused aswell ?
  
  */

  int inBIOS;


} memoryMap;


/*

  Interrupt Enable Register
  --------------------------- FFFF
  Internal RAM
  --------------------------- FF80
  Empty but unusable for I/O
  --------------------------- FF4C
  I/O ports
  --------------------------- FF00
  Empty but unusable for I/O
  --------------------------- FEA0
  Sprite Attrib Memory (OAM)
  --------------------------- FE00
  Echo of 8kB Internal RAM
  --------------------------- E000
  8kB Internal RAM
  --------------------------- C000
  8kB switchable RAM bank
  --------------------------- A000
  8kB Video RAM
  --------------------------- 8000 --
  16kB switchable ROM bank |
  --------------------------- 4000 |= 32kB Cartrigbe
  16kB ROM bank #0 |
  --------------------------- 0000 --

  */


//Returns size of file in bytes
long fileSize(FILE* file) {
  //Get length of file in bytes
  if (file) {

    //Save file pointer
    long current = ftell(file);

    //Seek to end
    fseek(file, 0, SEEK_END);

    //Get size
    long size = ftell(file);

    //Restore file pointer
    fseek(file, current, SEEK_SET);

    //Return size
    return size;
  }
  else {
    //Write to log
    return FILE_ERROR;
  }
}

//Loads a ROM into memory and returns a byte pointer to the data
byte* loadROM(FILE* file) {

  //Allocate enough memory for the file
  byte* buffer = malloc(sizeof(byte) * fileSize(file));

  //Read data into buffer
  fread(buffer, fileSize(file), sizeof(byte), file);

  //Don't forget to free this memory outside!
  return buffer;

}

//Initiliases the memory map and loads the rom file into memory (MUST BE CALLED BEFORE ANY READ/WRITE FUNCTIONS!)
void initialiseMemoryMap(FILE* rom) {

  //1. Set up BIOS

  //Flag set to read from the BIOS
  memoryMap.inBIOS = 1;

  byte bios[BIOS_SIZE] =
  { 
      0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
      0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
      0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
      0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
      0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
      0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
      0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
      0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
      0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
      0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
      0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
      0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
      0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
      0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
      0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
      0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
  };

  //Copy the first BIOS_SIZE bytes into ROM
  memcpy(memoryMap.bios, bios, BIOS_SIZE);
  
  /*
    When the CPU starts up, PC starts at 0000h, which is the start of the 256-byte GameBoy BIOS code. 
    Once the BIOS has run, it is removed from the memory map, and this area of the cartridge rom becomes addressable.
  */

  //2. Load Cartridge into memory
  memoryMap.rom = loadROM(rom);


}

//Reads a byte (1 byte) from an address in memory
byte readByte(byte* memory) {

  //Damn why can't I use bitwise operators on pointers?
  word address = (word)memory;

  switch (address & READ_ADDRESS_MASK) {

  //BIOS (256 bytes) ROM Bank 0
  case BIOS_ADDRESS: 

    if (memoryMap.inBIOS) {
      //If we want to read from the BIOS
      if (address < BIOS_SIZE) {
        return memoryMap.bios[address & READ_ADDRESS_MASK];
      } // else if () NEVER DECLARE TWICE! OH NOOOOOOO
    }

    break;

  default: return 1;

  }

  return 0;
}


void dummy() {

  FILE* rom = fopen("Pokemon Red.gb", "r");

  byte* romData = loadROM(rom);

  printf("First 256 bytes\n");
  for (int i = 0; i < 256; i++) {
    printf("%02X ", romData[i]);
  }

  printf("Rom size %d bytes\n", fileSize(rom));
  getchar();


}