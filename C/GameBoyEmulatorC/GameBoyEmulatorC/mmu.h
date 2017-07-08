#pragma once

//Include guard needed
#include <stdio.h>

#pragma warning(disable: 4996)

//Memory map constants
#define ROM_SIZE 32768
#define MEMORY_BANK_0_SIZE 8192
#define MEMORY_BANK_1_SIZE 8192
#define VRAM_SIZE 8192
#define INTERNAL_RAM_SIZE 8192
#define EXTERNAL_RAM_SIZE 8192
#define ZERO_PAGE_RAM_SIZE 128
#define BIOS_SIZE 256
#define CARTRIDGE_HEADER_SIZE 80

//Memory bounds for the Z80 
#define MEMORY_ADDRESS_MINIMUM 0x0000
#define MEMORY_ADDRESS_MAXIMUM 0xFFFF

//Mask constants
#define READ_ADDRESS_MASK 0xF000

//Memory addresses
#define BIOS_ADDRESS 0x0000

//This doesn't belong here
#define FILE_ERROR -1

typedef unsigned char byte;
typedef unsigned short word;

//Related functions & definitions

//Returns size of file in bytes
long fileSize(const char* fileName);

//Loads a ROM into memory and returns a byte poitner to the data
 byte* loadROM(FILE* file);

 //Initiliase the memory map and load the rom file into memory
 void initialiseMemoryMap(FILE* rom);

 //Reads a byte (1 byte ) from an address in memory
 byte readByte(byte* memory);

 //Reads a word (2 bytes) from an address in memory
 word readWord(byte* address);
 
 //Writes a byte to address
 void writeByte(byte* address, byte value);

 //Writes a word to address
 void writeWord(byte* address, word value);

 void dummy();