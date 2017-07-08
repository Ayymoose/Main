//Z80 CPU
//Details go here

#include "z80.h"

//Register flags
#define ZERO_FLAG 0x0080
#define HALF_CARRY_FLAG 0x0020
#define CARRY_FLAG 0x0010
#define OPERATION_FLAG 0x0040

struct CPU {
  //Registers
  int A;
  int B;
  int C;
  int D;
  int F;
  int SP; //Stack Pointer
  int PC; //Program Counter
} Z80;

void initialiseCPU() {

  //Clear all registers

  Z80.A = ZERO;
  Z80.B = ZERO;
  Z80.C = ZERO;
  Z80.D = ZERO;
  Z80.F = ZERO;
  Z80.PC = ZERO;
  Z80.SP = ZERO;


}

//Reset the CPU to initial state
void reset() {

}