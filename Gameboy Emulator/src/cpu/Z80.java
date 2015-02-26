package cpu;

public class Z80 {
  
  /*
   * Overview:
   * CPU: Zilog Z80 CPU was the CPU used in the original Gameboy.
   * Clock rate: 4.17MHz
   * Buses: 8-bit data bus
   * 
   */
  
  
  /*
   * 16 bit registers:
   * 
   * a :
   * b :
   * c :
   * d :
   * e :
   * h :
   * l :
   * f : Flags register
   * 
   * pc : Program Counter (Instruction Register/Pointer (IR/P)/
   * sp : Stack Pointer
   * 
   * 
   */
  
  Register pc = new Register((short) 0x00_00);
  Register sp = new Register((short) 0x00_00);
  
  Register a = new Register((short) 0x00_00);
  Register b = new Register((short) 0x00_00);
  Register c = new Register((short) 0x00_00);
  Register d = new Register((short) 0x00_00);
  Register e = new Register((short) 0x00_00);
  Register h = new Register((short) 0x00_00);
  Register l = new Register((short) 0x00_00);
  Register f = new Register((short) 0x00_00);
  
  /*
   * Internal Clocks:
   * 
   * m :
   * t :
   * 
   */
  
  Clock m = new Clock(0x00_00);
  Clock t = new Clock(0x00_00);
  

}
