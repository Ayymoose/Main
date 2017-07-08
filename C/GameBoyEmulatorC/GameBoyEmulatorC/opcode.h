#pragma once
#include <stdlib.h>
//Z80 opcodes go here
//8 bits -> 256 different opcodes (+256 more for bitwise operations)
//Who knew writing a disassembler was this easy?

#define OPCODE_COUNT 256


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


//Creates a new opcode and returns a pointer to a struct
struct opcode* createOpcode(char* name, int m_cycles, int t_cycles, int Z, int N, int H, int C) {
  struct opcode* opCode = malloc(sizeof(struct opcode));
  opCode->name = name;
  opCode->t_cycles = t_cycles;
  opCode->m_cycles = m_cycles;
  opCode->Z = Z;
  opCode->N = N;
  opCode->H = H;
  opCode->C = C;
  return opCode;
}

//Should go in a different file

//Creates an opcode map with size elements
//DO NOT FORGET TO FREE MEMORY
struct opcode** createOpcodeMap(int size) {

  //There are two tables; one for standard opcodes and one for bit related opcodes
  //If the prefix byte of the opcode is 'CB' it is accessed above 0xFF in the array

  return malloc(sizeof(struct opcode*) * size);
}

//Maps an opcode to the given map with a struct opcode
void mapOpcode(struct opcode** map, int opcode, struct opcode* opCode) {
  map[opcode] = opCode;
}

//Returns a pointer to an opcode in the given map
struct opcode* getOpcode(struct opcode** map, int opcodeValue) {
  return map[opcodeValue];
}

//

//Create the opcode mappings
void initiliaseOpcodeTable() {

  //It's gonna be real easy to create the disassembler once this is complete
  //Reference
  //http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html

  struct opcode** opcodeMapMain = createOpcodeMap(OPCODE_COUNT);
  struct opcode** opcodeMapCB = createOpcodeMap(OPCODE_COUNT);

  //Problem: Some instructions vary their cycle on whether action is taken or not
  //Handle before!
  mapOpcode(opcodeMapMain, 0x00, createOpcode("NOP", 1, 4, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x01, createOpcode("LD (BC) ,d16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x02, createOpcode("LD (BC) ,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x03, createOpcode("INC BC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x04, createOpcode("INC B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x05, createOpcode("DEC B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x06, createOpcode("LD B, d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x07, createOpcode("RLCA", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x08, createOpcode("LD a16, SP", 1, 4, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x09, createOpcode("ADD HL,BC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0A, createOpcode("LD A,(BC)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0B, createOpcode("DEC BC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0C, createOpcode("INC C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0D, createOpcode("DEC C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0E, createOpcode("LD C, d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x0F, createOpcode("RRCA", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x10, createOpcode("STOP 0", 1, 4, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x11, createOpcode("LD DE,d16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x12, createOpcode("LD (DE),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x13, createOpcode("INC DE", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x14, createOpcode("INC D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x15, createOpcode("DEC D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x16, createOpcode("LD D,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x17, createOpcode("RLA", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x18, createOpcode("JR r8", 1, 4, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x19, createOpcode("ADD HL,DE", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1A, createOpcode("LD A,(DE)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1B, createOpcode("DEC DE", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1C, createOpcode("INC E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1D, createOpcode("DEC E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1E, createOpcode("LD E, d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x1F, createOpcode("RRA", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x20, createOpcode("JR NZ,r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x21, createOpcode("LD HL,d16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x22, createOpcode("LD (HL+),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x23, createOpcode("INC HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x24, createOpcode("INC H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x25, createOpcode("DEC H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x26, createOpcode("LD H,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x27, createOpcode("DAA", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x28, createOpcode("JR Z,r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x29, createOpcode("ADD HL,HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2A, createOpcode("LD A,(HL+)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2B, createOpcode("DEC HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2C, createOpcode("INC L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2D, createOpcode("DEC L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2E, createOpcode("LD L,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x2F, createOpcode("CPL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x30, createOpcode("JR NC,r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x31, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x32, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x33, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x34, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x35, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x36, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x37, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x38, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x39, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x40, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x41, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x42, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x43, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x44, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x45, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x46, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x47, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x48, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x49, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x50, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x51, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x52, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x53, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x54, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x55, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x56, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x57, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x58, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x59, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x60, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x61, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x62, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x63, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x64, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x65, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x66, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x67, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x68, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x69, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x70, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x71, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x72, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x73, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x74, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x75, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x76, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x77, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x78, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x79, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x80, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x81, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x82, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x83, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x84, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x85, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x86, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x87, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x88, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x89, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x90, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x91, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x92, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x93, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x94, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x95, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x96, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x97, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x98, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x99, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xED, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFF, createOpcode("", 3, 12, 0, 0, 0, 0));
  //CB Table opcodes
  mapOpcode(opcodeMapCB, 0x00, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x01, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x02, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x03, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x04, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x05, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x06, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x07, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x08, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x09, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x10, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x11, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x12, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x13, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x14, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x15, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x16, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x17, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x18, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x19, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x20, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x21, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x22, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x23, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x24, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x25, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x26, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x27, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x28, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x29, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x30, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x31, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x32, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x33, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x34, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x35, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x36, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x37, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x38, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x39, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x40, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x41, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x42, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x43, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x44, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x45, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x46, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x47, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x48, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x49, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x50, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x51, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x52, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x53, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x54, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x55, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x56, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x57, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x58, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x59, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x60, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x61, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x62, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x63, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x64, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x65, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x66, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x67, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x68, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x69, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x70, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x71, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x72, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x73, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x74, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x75, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x76, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x77, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x78, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x79, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x80, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x81, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x82, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x83, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x84, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x85, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x86, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x87, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x88, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x89, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x90, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x91, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x92, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x93, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x94, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x95, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x96, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x97, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x98, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x99, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9A, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9B, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9C, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9D, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9E, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9F, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xED, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEF, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF0, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF1, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF2, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF3, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF4, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF5, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF6, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF7, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF8, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF9, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFA, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFB, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFC, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFD, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFE, createOpcode("", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFF, createOpcode("", 3, 12, 0, 0, 0, 0));

}