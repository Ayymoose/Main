//Entry point for main.c

typedef unsigned char byte;
typedef unsigned short word;

//Disable deprecation warnings


#include "mmu.h"
//#include "z80.h"
#include "opcode.h"

int main(int argc, char** argv) {
  
  //1. Load ROM into memory

  //2. Start Fetch-Decode-Execute cycle


  for (int i = 0x0; i <= 0xFF; i++) {
    printf("mapOpcode(opcodeMapCB, 0x%02X, createOpcode(\"\", 3, 12, 0, 0, 0, 0));\n",i);
  }
  getchar();
  //initiliaseOpcodeTable();

  //initialiseMemoryMap(fopen("Pokemon Red.gb", "r"));
  //printf("%d", readByte(0xFFFF));
  

  //dummy();
  
  return 0;
}