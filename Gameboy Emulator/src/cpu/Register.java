package cpu;

public class Register {
  
  /*
   * Registers used in the Z80 are 16-bits wide 
   */
  
  private short data;
  private final short REGISTER_WIDTH = 16;
  
  //Constructor
  public Register(short data) {
    this.data = data;
  }
  
  //Get register width
  public short registerWidth() {
    return REGISTER_WIDTH;
  }
  
  //Writes a word (16 bits) to the register
  public void writeWord(short word) {
    data = word;
  }

  //Clears a register
  public void clear() {
    data = 0x00_00;
  }
  
  //Writes a byte (unsigned?) to the high or low of the register
  public void writeByte(short byteToWrite,boolean highOrLow) {
    
  }
}
