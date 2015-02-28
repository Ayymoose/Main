package cpu;

public class Register {
  
  /*
   * Registers used in the Z80 are 16-bits wide (at most) or 8 bits minimum (at least)
   */
  
  //Register data
  private int data;
  private int flags;
  //private final int width;
  
  //Constants
  
  //Byte values
  private final int ZERO = 0x00_00; 
  private final int LOW_BYTE = 0xFF_00;
  private final int HIGH_BYTE = 0x00_FF;
  private final int BITS_IN_BYTE = 8;
  //
  
  //Data values
  private final int REGISTER_WIDTH = 16;
  //
  private final int REGISTER_MAX_VALUE = 0xFF_FF;
  private final int DATA_MAX_VALUE = 0xFF;
  //
  
  //Flags
  //Should go in another file globally available most likely
  // Set if the last operation produced a result of 0;
  private final int ZERO_FLAG = 0x80;
  //Set if the last operation was a subtraction;
  private final int OPERATION_FLAG = 0x40;
  //Set if, in the result of the last operation, the lower half of the byte overflowed past 15;
  private final int HALF_CARRY_FLAG = 0x20;
  //Set if the last operation produced a result over 255 (for additions) or under 0 (for subtractions).
  private final int CARRY_FLAG = 0x10;
  
  //Constructor
  public Register(int data) {
    this.data = data;
  }
  
  //Set the flags of the register (exclusive only to the flags register?)
  public void setFlag(int flag) {
    flags |= flag;
    
  
    /*switch (flag) {
    case ZERO_FLAG:
      flags |= ZERO_FLAG;
      break;
    case OPERATION_FLAG:
      break;
    case HALF_CARRY_FLAG:
      break;
    case CARRY_FLAG:
      flags |= CARRY_FLAG;
      break;
    default:
      break;
    }*/
  }
  
  //Get the data in the register
  public int getWord() {
    return data;
  }
  
  //Get register width
  public int registerWidth() {
    return REGISTER_WIDTH;
  }
  
  //Writes a word (16 bits) to the register
  public void writeWord(int word) {
    //Pre : 
    //Post : Writes word to the register
    if (word <= REGISTER_MAX_VALUE) {
      data = word;
    }// else {
      //Register overflow flag set
    //}  
  }

  //Clears a register
  public void clear() {
    //Pre - Post -
    data = ZERO;
  }
  
  //Returns the high byte stored in the register
  public int getHighByte() {
    //Pre - Post -
    return data >> BITS_IN_BYTE;
  }
  
  //Returns the low byte stored in the register
  public int getLowByte() {
    //Pre - Post -
    return data & HIGH_BYTE;
  }
  
  //Writes an unsigned to the high or low of the register
  public void writeByte(int byteToWrite,boolean high) {
    //Pre - byteToWrite is an unsigned 8 bit data (0-255)
    //Post - Writes byteToWrite to the high or low byte of the 16 bit word of the register
    if (high) {
      
      //Shift byteToWrite to high byte level
      byteToWrite <<= BITS_IN_BYTE;
      //Clear high byte of register
      data &= HIGH_BYTE;
      //Write byteToWrite to high byte of register
      data |= byteToWrite;
      
    } else {
      
      //Write to the low byte
      
      //Register
      //|   Unused        | | HIGH  | | LOW   |  
      //0000 0000 0000 0000 0000 0000 0101 0110 data
      //0000 0000 0000 0000 0101 0110 0000 0000 byteToWrite

      //Clear low byte of register
      data &= LOW_BYTE;
      //Set low byte to byteToWrite
      data |= byteToWrite;  
    }
  }
  
  //Adds value to this register
  public void add(int value) {
    //Value must be less than DATA_MAX_VALUE
    data += value;
  }
  
  //Adds value to register r
  public void add(Register r,int value) {
    r.add(value);
  }
  //add,copy,move
}
