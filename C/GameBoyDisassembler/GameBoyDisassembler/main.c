#include <stdio.h>
#include <stdlib.h>
#include "opcode.h"


struct opcode** opcodeMapMain;
struct opcode** opcodeMapCB;

#pragma warning (disable : 4996)

typedef unsigned char byte; //Should be globally defined 

//GameBoy begins executing instructions at 0x100 in memory
#define INSTRUCTION_EXECUTION_ADDRESS 0x100
#define PREFIX_CB 0xCB
#define MAXIMUM_OPCODE_LENGTH 16 //Ugh I'm unsure about this
#define OPERAND_COUNT 2
//

#define VERSION 1
#define AUTHOR "Moose"

/*

  Z80 GameBoy ROM disassembler in C
  Purpose: To further understand how hardware works (although unrelated here...) I mean to understand the structure of the GameBoy further.
  Command line: GameBoyDisassembler.exe <file_name> <number_of_lines_of_disassembly> (-f = entire file)

  Cool! I made a disassembler for the GameBoy in C!
  Next up! Cartridge information about a game!
  -Moose

*/

/*
  
  Bugs:
  1. The lines of disassembly is incorrect! 
  Everytime I encounter an opcode, I must decrement the counter 


  Problems:

  2. I do not free the allocated memory from the creation of the opcodes! Very bad!
  3. I'm using a hack to display the opcodes via re/allocation of the variable; I don't like this
  4. The opcode struct has unnecessary fields which I have done nothing about
  5. Do I need to care about endianess here?

  Possible features

  1. Cartridge information at the top
  2. Jump to address
  3. Commented assembly commands
  4. Statistics about file
  5. Code refactoring

*/

int main(int argc, char** argv) {
  
  //"E:\\Ayman\\Programming\\github\\Main\\C\\GameBoyEmulatorC\\GameBoyEmulatorC\\Pokemon Red.gb" 10 

  if (argc) {

    //GameBoyDisassembler.exe <file_name> <start_address_of_disassembly (default 0x100) <number_of_lines_of_disassembly> (-f = all)

    const char* fileName = argv[1];
    const int LINES_OF_DISASSEMBLY;
    sscanf(argv[2], "%d", &LINES_OF_DISASSEMBLY);
    int linesOfDisassembly = LINES_OF_DISASSEMBLY;

    //
    printf("GameBoy Disassembler C (GBC) version %d\nCreated by %s\n", VERSION, AUTHOR);
    printf("Disassembling %s\n", fileName);
    //

    //1. Load ROM into memory
    FILE* rom = fopen(fileName, "r");

    //2. Display disassembled code 
    if (rom) {

      //Size of file in bytes
      long size = fileSize(rom);

      //Pointer to the ROM data
      byte* romData = loadROM(rom);

      //Pointer to the data which we will use to disassemble the file
      //Point to start of execution in the ROM file
      long romPointer = INSTRUCTION_EXECUTION_ADDRESS;

      //Pointer to an opcode struct that contains information about the opcode
      struct opcode* opcode;

      //Length of the instruction (opcode + operand)
      byte instructionLength;

      //Initialises the table of opcodes
      initiliaseOpcodeTable();

      //Enum for instruction type
      enum instructionType {
        INSTRUCTION_NORMAL,
        INSTRUCTION_8,
        INSTRUCTION_16
      } instructionType;

      enum instructionType opcodeType;

      //Small array to hold the bytes of the operand
      byte operand[OPERAND_COUNT];

      //Print information at top
      printf(" -----------------------------------------------------\n");
      printf(" Address\t Opcode\t Operand(s)\t Disassembly\n");
      printf(" -----------------------------------------------------\n");
      // INSTRUCTION_EXECUTION_ADDRESS + LINES_OF_DISASSEMBLY
      //Loop through code
      while (romPointer < size && linesOfDisassembly) {

        //Read a byte
        byte instruction = romData[romPointer];

        //Decode it
        opcode = (instruction != PREFIX_CB ? getOpcode(opcodeMapMain, instruction) : getOpcode(opcodeMapCB, instruction = romData[++romPointer]));

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
          operand[0] = romData[romPointer + 1];
          operand[1] = 0x00;
          opcodeType = INSTRUCTION_8;
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
          operand[0] = romData[romPointer + 1];
          operand[1] = romData[romPointer + 2];
          opcodeType = INSTRUCTION_16;
          break;
        default:
          operand[0] = operand[1] = 0x00;
          instructionLength = 1;
          opcodeType = INSTRUCTION_NORMAL;
          break;
        }

        //Display

        //Dirty but it works
        byte* mnemonic = calloc(MAXIMUM_OPCODE_LENGTH, sizeof(byte)); //Could crash at some point
        int index, i; //Better names needed

        switch (opcodeType) {
        case INSTRUCTION_NORMAL:
          printf(" 0x%06X \t %02X \t -- \t\t %s \n", romPointer, instruction, opcode->name);
          break;
        case INSTRUCTION_8:
        case INSTRUCTION_16:
          index = i = 0;
          while (opcode->name[i]) {
            if (opcode->name[i] == '%') {
              switch (opcode->name[i + 1]) {
              case 'w':
                sprintf(mnemonic + index, "0x%02X%02X", operand[1], operand[0]);
                index += 6; //Length of string in sprintf
                break;
              case 'b':
                sprintf(mnemonic + index, "0x%02X", operand[0]);
                index += 4;
                break;
              case 'r':
                sprintf(mnemonic + index, "(PC+0x%02X)", operand[0]);
                index += 9;
                break;
              }
              i++;
            }
            else {
              mnemonic[index] = opcode->name[i];
              index++;
            }
            i++;
          }
          if (opcodeType == INSTRUCTION_8) {
            printf(" 0x%06X \t %02X \t %02X \t\t %s \n", romPointer, instruction, operand[0], mnemonic);
          }
          else {
            printf(" 0x%06X \t %02X \t %02X%02X \t\t %s \n", romPointer, instruction, operand[1], operand[0], mnemonic);
          }

          free(mnemonic);
          break;
        }
        linesOfDisassembly--;
        //Advance romPointer by how many bytes the instruction (opcode + operand) took
        romPointer += instructionLength;
      }

      //Free allocated memory
      //I forgot to free all the opcodes in the table! -> I don't think I've freed the array properly (if it's 2D then I can free the opcodes)
      free(opcodeMapMain);
      free(opcodeMapCB);
      free(romData);

      printf("Displaying %d lines of disassembly.\n", LINES_OF_DISASSEMBLY);
      //printf("Jump to address: "); Next Version!
      printf("Press any key to exit...");

      getchar();
    }
  }
  
  return 0;
}