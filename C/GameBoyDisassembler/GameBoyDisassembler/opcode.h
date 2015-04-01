#pragma once

#include <stdio.h>


//26kB for 512 opcodes when using ints
struct opcode {
  char* name;     /* Name of opcode                                 */
  int t_cycles;   /* How many T (time) cycles this instruction take */
  int m_cycles;   /* How many M (machine) cycles instruction takes  */

                  //Flags affected
                  //0 = Unaffected , 1 = Affected
  int Z; //Zero
  int N; //Subtract 
  int H; //Half Carry
  int C; //Carry
};

extern struct opcode** opcodeMapMain;
extern struct opcode** opcodeMapCB;


typedef unsigned char byte;

//Returns size of file in bytes
long fileSize(FILE* file);

//Loads a ROM into memory and returns a byte pointer to the data
byte* loadROM(FILE* file);

//Creates a new opcode and returns a pointer to a struct
struct opcode* createOpcode(char* name, int m_cycles, int t_cycles, int Z, int N, int H, int C);

//Creates an opcode map with size elements
struct opcode** createOpcodeMap(int size);

//Maps an opcode to the given map with a struct opcode
void mapOpcode(struct opcode** map, int opcode, struct opcode* opCode);

//Returns a pointer to an opcode in the given map
struct opcode* getOpcode(struct opcode** map, int opcodeValue);

//Create the opcode mappings
void initiliaseOpcodeTable();

