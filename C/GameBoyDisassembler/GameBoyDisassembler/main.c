#include <stdio.h>
#include <stdlib.h>
#include "opcode.h"

struct opcode** opcodeMapMain;
struct opcode** opcodeMapCB;

#pragma warning (disable : 4996)

typedef unsigned char byte;

//GameBoy begins executing instructions at 0x100 in memory
#define INSTRUCTION_EXECUTION_ADDRESS 0x100
#define PREFIX_CB 0xCB
/*

  Z80 GameBoy ROM disassembler in C
  Purpose: -
  Command line: GameBoyDisassembler.exe <file_name> <number_of_lines_of_disassembly>

*/

/*
  
  Problems:

  1. Cannot figure out a way to display the actual address or operand instead of a/d/8/16 in the opcode name.

  Possible features

  1. Cartridge information at the top
  2. Jump to address
  3. Commented assembly commands
  4. Statistics about file
  5. Code refactoring
  6. Command line input

*/

int main(int argc, char** argv) {

  //1. Load ROM into memory
  FILE* rom = fopen("E:\\Ayman\\Programming\\github\\Main\\C\\GameBoyEmulatorC\\GameBoyEmulatorC\\Pokemon Red.gb", "r");

  //2. Display disassembled code 
  if (rom) {

    //Size of file in bytes
    long size = INSTRUCTION_EXECUTION_ADDRESS + 100;//fileSize(rom);

    //Pointer to the ROM data
    byte* romData = loadROM(rom);

    //Pointer to the data which we will use to disassemble the file
    long romPointer = INSTRUCTION_EXECUTION_ADDRESS;

    //Pointer to an opcode struct that contains information about the opcode
    struct opcode* opc;

    //Length of the instruction (opcode + operand)
    byte instructionLength;

    //Initialises the table of opcodes
    initiliaseOpcodeTable();

    //Pointers became null somehow
    if (opcodeMapCB == NULL || opcodeMapMain == NULL) {
      printf("%06X\n%06X\n",opcodeMapMain, opcodeMapCB);
      getchar();
      exit(-1);
    }

    //Small array to hold the bytes of the operand
    byte address[2];

    //Print information at top
    printf(" ---------------------------------------------\n");
    printf(" Address\t Opcode\t Disassembled Commands\n"); //Oooo! Add operand column too!
    printf(" ---------------------------------------------\n");

    //Loop through code
    while (romPointer < size) {
      
      //Read a byte
      byte instruction = romData[romPointer];     

      //Decode it
      opc = (instruction != PREFIX_CB ? getOpcode(opcodeMapMain, instruction) : getOpcode(opcodeMapCB, instruction));

      //Err what was the endianess of the Z80?
      //For display purposes and incrementing the romPointer
      //We must calculate the length of the instruction

      switch (instruction) {
        //8 Bit
        case 0x06: //LD B, d8
        case 0x0E: //LD C, d8
        case 0x16: //LD D,d8
        case 0x18: //JR r8
        case 0x1E: //LD E, d8
        case 0x20: //JR NZ,r8
        case 0x26: //LD H,d8
        case 0x28: //JR Z,r8
        case 0x2E: //LD L,d8
        case 0x30: //JR NC,r8
        case 0x36: //LD (HL),d8
        case 0x38: //JR C,r8
        case 0x3E: //LD A,d8
        case 0xC6: //ADD A,d8
        case 0xCE: //ADC A,d8
        case 0xD6: //SUB d8
        case 0xDE: //SBC A,d8
        case 0xE0: //LDH (a8),A
        case 0xE6: //AND d8
        case 0xE8: //ADD SP,r8
        case 0xEE: //XOR d8
        case 0xF0: //LDH A,(a8)
        case 0xF6: //OR d8
        case 0xF8: //LD HL,SP+r8
        case 0xFE: //CP d8
          instructionLength = 2;
          address[0] = romData[romPointer + 1];
          address[1] = 0x00;
          break; 
        //16-bit 
        case 0x01: //LD (BC) ,d16  
        case 0x08: //LD a16, SP
        case 0x11: //LD DE,d16
        case 0x21: //LD HL,d16
        case 0x31: //LD SP,d16
        case 0xC2: //JP NZ,a16
        case 0xC3: //JP a16
        case 0xC4: //CALL NZ,a16
        case 0xCA: //JP Z,a16
        case 0xCC: //CALL Z,a16
        case 0xCD: //CALL a16
        case 0xD2: //JP NC,a16
        case 0xD4: //CALL NC,a16
        case 0xDA: //JP C,a16
        case 0xDC: //CALL C,a16
        case 0xEA: //LD (a16),A
        case 0xFA: //LD A,(a16)
          instructionLength = 3;
          address[0] = romData[romPointer + 1];
          address[1] = romData[romPointer + 2];
        break;
        default:
          address[0] = address[1] = 0x00;
          instructionLength = 1;
          break;
      }

      //Display e.g
      //0x000000 FB NOP
      printf(" 0x%06X \t %02X \t %s ", romPointer, instruction, opc->name);
      printf((instructionLength == 1 ? "\n" : "0x%02X%02X \n"),address[1],address[0]);

      //Advance romPointer by how many bytes the instruction (opcode + operand) took
      romPointer+=instructionLength;
    }

    //Free allocated memory
    free(opcodeMapMain);
    free(opcodeMapCB);
    free(romData);

    printf("Displaying %d lines of disassembly.\n", size - INSTRUCTION_EXECUTION_ADDRESS);
    printf("Press any key to exit...");
    getchar();
  } 
  
  return 0;
}