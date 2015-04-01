#include <stdlib.h>
#include <stdio.h>
#include "opcode.h"

#define FILE_ERROR -1

typedef unsigned char byte;

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

//Loads a ROM into memory and returns a byte pointer to the data (NULL if the FILE isn't valid)
byte* loadROM(FILE* file) {

  if (file) {

    //Allocate enough memory for the file
    byte* buffer = malloc(sizeof(byte) * fileSize(file));

    //Read data into buffer
    fread(buffer, fileSize(file), sizeof(byte), file);

    //Don't forget to free this memory outside!
    return buffer;

  }
  else {
    return NULL;
  }

}

//Z80 opcodes go here
//8 bits -> 256 different opcodes (+256 more for bitwise operations)
//Who knew writing a disassembler was this easy?

#define OPCODE_COUNT 256

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

  //Must free after use
  opcodeMapMain = createOpcodeMap(OPCODE_COUNT);
  opcodeMapCB = createOpcodeMap(OPCODE_COUNT);

  //Problem: Some instructions vary their cycle on whether action is taken or not
  //Handle before!
  //Additional information other than the name have no meaning here as I just C&P'ed from the other file
  //It's really just a waste of space actually.
  //Well I could have an option to get more detail about the opcode.
  //Meh.
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
  mapOpcode(opcodeMapMain, 0x31, createOpcode("LD SP,d16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x32, createOpcode("LD (HL-),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x33, createOpcode("INC SP", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x34, createOpcode("INC (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x35, createOpcode("DEC (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x36, createOpcode("LD (HL),d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x37, createOpcode("SCF", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x38, createOpcode("JR C,r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x39, createOpcode("ADD HL,SP", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3A, createOpcode("LD A,(HL-)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3B, createOpcode("DEC SP", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3C, createOpcode("INC A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3D, createOpcode("DEC A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3E, createOpcode("LD A,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x3F, createOpcode("CCF", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x40, createOpcode("LD B,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x41, createOpcode("LD B,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x42, createOpcode("LD B,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x43, createOpcode("LD B,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x44, createOpcode("LD B,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x45, createOpcode("LD B,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x46, createOpcode("LD B,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x47, createOpcode("LD B,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x48, createOpcode("LD C,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x49, createOpcode("LD C,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4A, createOpcode("LD C,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4B, createOpcode("LD C,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4C, createOpcode("LD C,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4D, createOpcode("LD C,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4E, createOpcode("LD C,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x4F, createOpcode("LD C,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x50, createOpcode("LD D,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x51, createOpcode("LD D,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x52, createOpcode("LD D,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x53, createOpcode("LD D,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x54, createOpcode("LD D,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x55, createOpcode("LD D,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x56, createOpcode("LD D,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x57, createOpcode("LD D,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x58, createOpcode("LD E,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x59, createOpcode("LD E,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5A, createOpcode("LD E,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5B, createOpcode("LD E,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5C, createOpcode("LD E,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5D, createOpcode("LD E,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5E, createOpcode("LD E,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x5F, createOpcode("LD E,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x60, createOpcode("LD H,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x61, createOpcode("LD H,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x62, createOpcode("LD H,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x63, createOpcode("LD H,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x64, createOpcode("LD H,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x65, createOpcode("LD H,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x66, createOpcode("LD H,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x67, createOpcode("LD H,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x68, createOpcode("LD L,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x69, createOpcode("LD L,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6A, createOpcode("LD L,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6B, createOpcode("LD L,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6C, createOpcode("LD L,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6D, createOpcode("LD L,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6E, createOpcode("LD L,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x6F, createOpcode("LD L,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x70, createOpcode("LD (HL),B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x71, createOpcode("LD (HL),C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x72, createOpcode("LD (HL),D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x73, createOpcode("LD (HL),E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x74, createOpcode("LD (HL),H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x75, createOpcode("LD (HL),L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x76, createOpcode("HALT", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x77, createOpcode("LD (HL),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x78, createOpcode("LD A,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x79, createOpcode("LD A,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7A, createOpcode("LD A,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7B, createOpcode("LD A,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7C, createOpcode("LD A,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7D, createOpcode("LD A,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7E, createOpcode("LD A,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x7F, createOpcode("LD A,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x80, createOpcode("ADD A,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x81, createOpcode("ADD A,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x82, createOpcode("ADD A,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x83, createOpcode("ADD A,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x84, createOpcode("ADD A,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x85, createOpcode("ADD A,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x86, createOpcode("ADD A,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x87, createOpcode("ADD A,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x88, createOpcode("ADC A,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x89, createOpcode("ADC A,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8A, createOpcode("ADC A,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8B, createOpcode("ADC A,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8C, createOpcode("ADC A,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8D, createOpcode("ADC A,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8E, createOpcode("ADC A,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x8F, createOpcode("ADC A,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x90, createOpcode("SUB B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x91, createOpcode("SUB C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x92, createOpcode("SUB D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x93, createOpcode("SUB E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x94, createOpcode("SUB H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x95, createOpcode("SUB L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x96, createOpcode("SUB (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x97, createOpcode("SUB A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x98, createOpcode("SBC A,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x99, createOpcode("SBC A,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9A, createOpcode("SBC A,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9B, createOpcode("SBC A,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9C, createOpcode("SBC A,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9D, createOpcode("SBC A,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9E, createOpcode("SBC A,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0x9F, createOpcode("SBC A,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA0, createOpcode("AND B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA1, createOpcode("AND C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA2, createOpcode("AND D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA3, createOpcode("AND E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA4, createOpcode("AND H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA5, createOpcode("AND L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA6, createOpcode("AND (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA7, createOpcode("AND A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA8, createOpcode("XOR B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xA9, createOpcode("XOR C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAA, createOpcode("XOR D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAB, createOpcode("XOR E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAC, createOpcode("XOR H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAD, createOpcode("XOR L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAE, createOpcode("XOR (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xAF, createOpcode("XOR A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB0, createOpcode("OR B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB1, createOpcode("OR C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB2, createOpcode("OR D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB3, createOpcode("OR E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB4, createOpcode("OR H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB5, createOpcode("OR L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB6, createOpcode("OR (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB7, createOpcode("OR A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB8, createOpcode("CP B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xB9, createOpcode("CP C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBA, createOpcode("CP D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBB, createOpcode("CP E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBC, createOpcode("CP H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBD, createOpcode("CP L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBE, createOpcode("CP (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xBF, createOpcode("CP A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC0, createOpcode("RET NZ", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC1, createOpcode("POP BC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC2, createOpcode("JP NZ,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC3, createOpcode("JP a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC4, createOpcode("CALL NZ,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC5, createOpcode("PUSH BC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC6, createOpcode("ADD A,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC7, createOpcode("RST 00H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC8, createOpcode("RET Z", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xC9, createOpcode("RET", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCA, createOpcode("JP Z,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCB, createOpcode("PREFIX CB", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCC, createOpcode("CALL Z,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCD, createOpcode("CALL a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCE, createOpcode("ADC A,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xCF, createOpcode("RST 08H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD0, createOpcode("RET NC", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD1, createOpcode("POP DE", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD2, createOpcode("JP NC,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD3, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD4, createOpcode("CALL NC,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD5, createOpcode("PUSH DE", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD6, createOpcode("SUB d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD7, createOpcode("RST 10H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD8, createOpcode("RET C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xD9, createOpcode("RETI", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDA, createOpcode("JP C,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDB, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDC, createOpcode("CALL C,a16", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDD, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDE, createOpcode("SBC A,d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xDF, createOpcode("RST 18H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE0, createOpcode("LDH (a8),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE1, createOpcode("POP HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE2, createOpcode("LD (C),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE3, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE4, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE5, createOpcode("PUSH HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE6, createOpcode("AND d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE7, createOpcode("RST 20H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE8, createOpcode("ADD SP,r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xE9, createOpcode("JP (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEA, createOpcode("LD (a16),A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEB, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEC, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xED, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEE, createOpcode("XOR d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xEF, createOpcode("RST 28H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF0, createOpcode("LDH A,(a8)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF1, createOpcode("POP AF", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF2, createOpcode("LD A,(C)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF3, createOpcode("DI", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF4, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF5, createOpcode("PUSH AF", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF6, createOpcode("OR d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF7, createOpcode("RST 30H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF8, createOpcode("LD HL,SP+r8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xF9, createOpcode("LD SP,HL", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFA, createOpcode("LD A,(a16)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFB, createOpcode("EI", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFC, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFD, createOpcode("N/A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFE, createOpcode("CP d8", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapMain, 0xFF, createOpcode("RST 38H", 3, 12, 0, 0, 0, 0));

  //CB Table opcodes
  mapOpcode(opcodeMapCB, 0x00, createOpcode("RLC B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x01, createOpcode("RLC C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x02, createOpcode("RLC D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x03, createOpcode("RLC E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x04, createOpcode("RLC H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x05, createOpcode("RLC L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x06, createOpcode("RLC (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x07, createOpcode("RLC A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x08, createOpcode("RRC B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x09, createOpcode("RRC C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0A, createOpcode("RRC D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0B, createOpcode("RRC E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0C, createOpcode("RRC H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0D, createOpcode("RRC L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0E, createOpcode("RRC (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x0F, createOpcode("RRC A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x10, createOpcode("RL B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x11, createOpcode("RL C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x12, createOpcode("RL D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x13, createOpcode("RL E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x14, createOpcode("RL H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x15, createOpcode("RL L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x16, createOpcode("RL (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x17, createOpcode("RL A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x18, createOpcode("RR B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x19, createOpcode("RR C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1A, createOpcode("RR D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1B, createOpcode("RR E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1C, createOpcode("RR H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1D, createOpcode("RR L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1E, createOpcode("RR (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x1F, createOpcode("RR A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x20, createOpcode("SLA B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x21, createOpcode("SLA C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x22, createOpcode("SLA D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x23, createOpcode("SLA E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x24, createOpcode("SLA H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x25, createOpcode("SLA L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x26, createOpcode("SLA (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x27, createOpcode("SLA A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x28, createOpcode("SRA B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x29, createOpcode("SRA C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2A, createOpcode("SRA D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2B, createOpcode("SRA E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2C, createOpcode("SRA H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2D, createOpcode("SRA L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2E, createOpcode("SRA (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x2F, createOpcode("SRA A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x30, createOpcode("SWAP B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x31, createOpcode("SWAP C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x32, createOpcode("SWAP D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x33, createOpcode("SWAP E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x34, createOpcode("SWAP H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x35, createOpcode("SWAP L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x36, createOpcode("SWAP (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x37, createOpcode("SWAP A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x38, createOpcode("SRL B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x39, createOpcode("SRL C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3A, createOpcode("SRL D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3B, createOpcode("SRL E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3C, createOpcode("SRL H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3D, createOpcode("SRL L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3E, createOpcode("SRL (HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x3F, createOpcode("SRL A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x40, createOpcode("BIT 0,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x41, createOpcode("BIT 0,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x42, createOpcode("BIT 0,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x43, createOpcode("BIT 0,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x44, createOpcode("BIT 0,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x45, createOpcode("BIT 0,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x46, createOpcode("BIT 0,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x47, createOpcode("BIT 0,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x48, createOpcode("BIT 1,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x49, createOpcode("BIT 1,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4A, createOpcode("BIT 1,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4B, createOpcode("BIT 1,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4C, createOpcode("BIT 1,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4D, createOpcode("BIT 1,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4E, createOpcode("BIT 1,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x4F, createOpcode("BIT 1,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x50, createOpcode("BIT 2,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x51, createOpcode("BIT 2,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x52, createOpcode("BIT 2,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x53, createOpcode("BIT 2,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x54, createOpcode("BIT 2,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x55, createOpcode("BIT 2,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x56, createOpcode("BIT 2,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x57, createOpcode("BIT 2,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x58, createOpcode("BIT 3,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x59, createOpcode("BIT 3,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5A, createOpcode("BIT 3,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5B, createOpcode("BIT 3,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5C, createOpcode("BIT 3,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5D, createOpcode("BIT 3,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5E, createOpcode("BIT 3,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x5F, createOpcode("BIT 3,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x60, createOpcode("BIT 4,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x61, createOpcode("BIT 4,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x62, createOpcode("BIT 4,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x63, createOpcode("BIT 4,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x64, createOpcode("BIT 4,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x65, createOpcode("BIT 4,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x66, createOpcode("BIT 4,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x67, createOpcode("BIT 4,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x68, createOpcode("BIT 5,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x69, createOpcode("BIT 5,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6A, createOpcode("BIT 5,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6B, createOpcode("BIT 5,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6C, createOpcode("BIT 5,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6D, createOpcode("BIT 5,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6E, createOpcode("BIT 5,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x6F, createOpcode("BIT 5,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x70, createOpcode("BIT 6,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x71, createOpcode("BIT 6,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x72, createOpcode("BIT 6,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x73, createOpcode("BIT 6,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x74, createOpcode("BIT 6,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x75, createOpcode("BIT 6,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x76, createOpcode("BIT 6,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x77, createOpcode("BIT 6,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x78, createOpcode("BIT 7,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x79, createOpcode("BIT 7,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7A, createOpcode("BIT 7,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7B, createOpcode("BIT 7,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7C, createOpcode("BIT 7,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7D, createOpcode("BIT 7,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7E, createOpcode("BIT 7,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x7F, createOpcode("BIT 7,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x80, createOpcode("RES 0,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x81, createOpcode("RES 0,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x82, createOpcode("RES 0,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x83, createOpcode("RES 0,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x84, createOpcode("RES 0,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x85, createOpcode("RES 0,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x86, createOpcode("RES 0,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x87, createOpcode("RES 0,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x88, createOpcode("RES 1,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x89, createOpcode("RES 1,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8A, createOpcode("RES 1,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8B, createOpcode("RES 1,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8C, createOpcode("RES 1,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8D, createOpcode("RES 1,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8E, createOpcode("RES 1,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x8F, createOpcode("RES 1,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x90, createOpcode("RES 2,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x91, createOpcode("RES 2,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x92, createOpcode("RES 2,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x93, createOpcode("RES 2,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x94, createOpcode("RES 2,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x95, createOpcode("RES 2,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x96, createOpcode("RES 2,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x97, createOpcode("RES 2,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x98, createOpcode("RES 3,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x99, createOpcode("RES 3,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9A, createOpcode("RES 3,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9B, createOpcode("RES 3,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9C, createOpcode("RES 3,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9D, createOpcode("RES 3,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9E, createOpcode("RES 3,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0x9F, createOpcode("RES 3,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA0, createOpcode("RES 4,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA1, createOpcode("RES 4,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA2, createOpcode("RES 4,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA3, createOpcode("RES 4,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA4, createOpcode("RES 4,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA5, createOpcode("RES 4,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA6, createOpcode("RES 4,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA7, createOpcode("RES 4,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA8, createOpcode("RES 5,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xA9, createOpcode("RES 5,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAA, createOpcode("RES 5,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAB, createOpcode("RES 5,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAC, createOpcode("RES 5,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAD, createOpcode("RES 5,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAE, createOpcode("RES 5,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xAF, createOpcode("RES 5,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB0, createOpcode("RES 6,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB1, createOpcode("RES 6,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB2, createOpcode("RES 6,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB3, createOpcode("RES 6,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB4, createOpcode("RES 6,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB5, createOpcode("RES 6,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB6, createOpcode("RES 6,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB7, createOpcode("RES 6,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB8, createOpcode("RES 7,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xB9, createOpcode("RES 7,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBA, createOpcode("RES 7,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBB, createOpcode("RES 7,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBC, createOpcode("RES 7,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBD, createOpcode("RES 7,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBE, createOpcode("RES 7,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xBF, createOpcode("RES 7,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC0, createOpcode("SET 0,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC1, createOpcode("SET 0,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC2, createOpcode("SET 0,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC3, createOpcode("SET 0,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC4, createOpcode("SET 0,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC5, createOpcode("SET 0,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC6, createOpcode("SET 0,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC7, createOpcode("SET 0,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC8, createOpcode("SET 1,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xC9, createOpcode("SET 1,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCA, createOpcode("SET 1,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCB, createOpcode("SET 1,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCC, createOpcode("SET 1,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCD, createOpcode("SET 1,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCE, createOpcode("SET 1,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xCF, createOpcode("SET 1,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD0, createOpcode("SET 2,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD1, createOpcode("SET 2,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD2, createOpcode("SET 2,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD3, createOpcode("SET 2,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD4, createOpcode("SET 2,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD5, createOpcode("SET 2,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD6, createOpcode("SET 2,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD7, createOpcode("SET 2,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD8, createOpcode("SET 3,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xD9, createOpcode("SET 3,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDA, createOpcode("SET 3,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDB, createOpcode("SET 3,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDC, createOpcode("SET 3,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDD, createOpcode("SET 3,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDE, createOpcode("SET 3,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xDF, createOpcode("SET 3,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE0, createOpcode("SET 4,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE1, createOpcode("SET 4,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE2, createOpcode("SET 4,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE3, createOpcode("SET 4,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE4, createOpcode("SET 4,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE5, createOpcode("SET 4,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE6, createOpcode("SET 4,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE7, createOpcode("SET 4,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE8, createOpcode("SET 5,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xE9, createOpcode("SET 5,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEA, createOpcode("SET 5,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEB, createOpcode("SET 5,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEC, createOpcode("SET 5,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xED, createOpcode("SET 5,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEE, createOpcode("SET 5,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xEF, createOpcode("SET 5,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF0, createOpcode("SET 6,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF1, createOpcode("SET 6,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF2, createOpcode("SET 6,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF3, createOpcode("SET 6,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF4, createOpcode("SET 6,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF5, createOpcode("SET 6,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF6, createOpcode("SET 6,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF7, createOpcode("SET 6,A", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF8, createOpcode("SET 7,B", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xF9, createOpcode("SET 7,C", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFA, createOpcode("SET 7,D", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFB, createOpcode("SET 7,E", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFC, createOpcode("SET 7,H", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFD, createOpcode("SET 7,L", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFE, createOpcode("SET 7,(HL)", 3, 12, 0, 0, 0, 0));
  mapOpcode(opcodeMapCB, 0xFF, createOpcode("SET 7,A", 3, 12, 0, 0, 0, 0));

}