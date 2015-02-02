package turtle;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class TurtleInterpreter {
  
  /*
     The interpreter part of your program should not see the tokens (and certainly never the raw input). 
     Instead it should be told what methods to execute and what values those methods parameters have.
     
     A TurtleInterpreter is responsible for managing the mapping of turtle names to turtle instances,
     keeping track of the current paper, and knowing where to read input from and to send output to.
   */
  
  //Processes input from an InputStream and writes the output to an OutputStream out
  public void process(InputStream in,PrintStream out) {
    
    //Default delimiter is ' ' (Space)
    Scanner scanner = new Scanner(in);
    Parser p = new Parser(scanner);
   
    //Get the commands to call the appropriate methods
    String[] cmds = p.parse();
    
    //Don't process and garbage
    if (cmds != null) {
    
    switch (cmds[0]) {
      case "paper":
        
        int width = Integer.parseInt(cmds[1]);
        int height = Integer.parseInt(cmds[2]);
        Paper paper = new Paper(width,height);
        out.println(paper.toString());
        
        break;
      case "new":
        break;
      case "pen":
      
        break;
      case "move":
        break;
      case "right":
        break;
      default:
        //show
        
        break;
        
    }
    
    }
    
  
    

    
  }
  
  
  
  /*
   * 
   * 1. paper width height which sets the paper size to width characters wide, and height characters
     high. Additionally, all locations should be blanked and all turtles removed.
     
     2. new type name x y which creates a new turtle. For Part 1, you can assume type will always
        be the string value normal (but see §2.2).
        The turtle should be named name, and all future commands will be directed to that turtle
        using this name. The turtle will be placed at position (x,y) on the paper, where position
        (0,0) is the bottom left corner. The turtle will have its pen up, with the brush character ‘*’
        and be facing North.

        Java Turtle Graphics Part 1: Implementing the Basics
     3. pen name state which changes the state of the pen held by turtle name. state can either be
        up, down, or a single non-blank character.
        The literal values up and down lift and drop the pen respectively; any other value will be
        interpreted as the turtle’s new brush character.
     4. move name distance which will instruct the turtle named name to move distance units in
        its current direction.
     5. right name angle and left name angle which will instruct the turtle named name to rotate
        angle degrees clockwise (right) or anti-clockwise (left, also known as counterclockwise).
        Assume that the angle parameter is a positive integer multiple of 45.
     6. show which will output the contents of the paper to the current output stream.
   * 
   * 
   */
  
  
  
  

}
