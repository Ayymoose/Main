package turtle;

import java.io.FileNotFoundException;

import util.Direction;
import util.Pen;
import util.Rotation;


public class Main {
  
  
  
  /*
   * The main method should check the program’s arguments to see where the input should be
     read from and where the output should be written to. 
     
     It should also create the appropriate
     Scanner and PrintStream instances. It should then create a new TurtleInterpreter, and use the
     aforementioned public method to process the commands in the input.
   */

    public static void main(String[] args) throws FileNotFoundException {
      
      //Now
      //input is from command line
      //output is via command line
      
      TurtleInterpreter tp = new TurtleInterpreter();
      
      while (true) {
      
      //Read from System.in and output to System.out
      tp.process(System.in,System.out);
      
      }
      
      
      
     
    }
}
