package cpu;


//This class should not be in cpu
public class Z80 {
  
  /*
   * Overview:
   * CPU: Zilog Z80 CPU was the CPU used in the original Gameboy.
   * Clock rate: 4.17MHz
   * Buses: 8-bit data bus -> 256 opcodes
   * Little Endian?
   * 
   */
  
  
  //public Z80(Register... rs) {
  //  
  //}
  
  /*
   * 16 bit registers:
   * pc : Program Counter (Instruction Register/Pointer (IR/P)/
   * sp : Stack Pointer
   */
  
  //Program counter initially points to 0x00_00 in memory?
  private Register pc = new Register(0x00_00);
  private Register sp = new Register(0x00_00);
  
  /*
   * 8 bit registers
   * a :
   * b :
   * c :
   * d :
   * e :
   * h :
   * l :
   * f : Flags register
   */
  
  private Register a = new Register(0x00_00);
  private Register b = new Register(0x00_00);
  private Register c = new Register(0x00_00);
  private Register d = new Register(0x00_00);
  private Register e = new Register(0x00_00);
  private Register h = new Register(0x00_00);
  private Register l = new Register(0x00_00);
  private Register f = new Register(0x00_00);
  
  
  /*
   * Internal Clocks:
   * 
   * m :
   * t :
   * 
   */
  
  private Clock m = new Clock(0x00_00);
  private Clock t = new Clock(0x00_00);
  
  
  //ADD A,E
  
  //Adds E to A storing result in A
  public void addR_E() {
    
    //Perform the addition
    a.add(e.getWord());
    
    //Clear the flags register
    f.clear();
    
    //Check for zero
    if (!((a.getLowByte() & 255) == 0)) {
     // f.setFlag(ZERO_FLAG);
    } 
    
    //Check for carry
    if (a.getLowByte() > 255) {
      //f.setFlag(CARRY_FLAG);
    }
    
    //Mask to 8 bits
    a.writeByte(0xFF, false);
  
    m.setTime(1);
    
    //Cycles taken?
    t.setTime(4);
  }

}
