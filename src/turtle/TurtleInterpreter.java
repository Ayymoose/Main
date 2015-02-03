package turtle;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import util.Direction;
import util.Pen;
import util.Rotation;

public class TurtleInterpreter {
  
  
  
  /*
   * Bug list:
   * 1. Rotation doesn't work properly
   * 2. Parsing code is a fucking mess
   * 3. Must not allow spaces as names
   * 
   */
  
  /*
     The interpreter part of your program should not see the tokens (and certainly never the raw input). 
     Instead it should be told what methods to execute and what values those methods parameters have.
     
     A TurtleInterpreter is responsible for managing the mapping of turtle names to turtle instances,
     keeping track of the current paper, and knowing where to read input from and to send output to.
   */
  
  //(Name,Turtle)
  private final Map<String,Turtle> turtles = new HashMap<String, Turtle>();
  private Paper currentPaper = null;
  
  //Processes input from an InputStream and writes the output to an OutputStream out
  public void process(InputStream in,PrintStream out) {
    
    //Default delimiter is ' ' (Space)
    Parser parser = new Parser(new Scanner(in));
    
    //Turtle details
    Turtle currentTurtle = null;
    String turtleName = null;
    
    
    //
   
    //Get the commands to call the appropriate methods
    String[] cmds = parser.parse();
    
    //Don't process garbage
    if (cmds != null) {
    
    switch (cmds[0]) {
      case "paper":
        
        int width = Integer.parseInt(cmds[1]);
        int height = Integer.parseInt(cmds[2]);
        Paper paper = new Paper(width,height);
        currentPaper = paper;

        break;
      case "new":

        //What to do with this now?
      //type for now will be "normal" (assumed!)
        String type = cmds[1];
        
        Coordinate position = new Coordinate(Integer.parseInt(cmds[3]),Integer.parseInt(cmds[4]));
        Turtle turtle = new Turtle(position,Direction.SOUTH_WEST,Pen.UP,currentPaper);
        
        turtleName = cmds[2];
        
        //Append the turtle to the hashmap
        turtles.put(turtleName,turtle);
        turtles.get(turtleName).changeBrush('*');
        break;
      case "pen":
        //pen name state
        //Untested
      
        turtleName = cmds[1];
        
        //Check if there is a turtle called name
        if (turtles.containsKey(turtleName)) {
          
          currentTurtle = turtles.get(turtleName);
          String state = cmds[2];
          
          switch (state) {
            case "up":
              currentTurtle.changePen(Pen.UP);
              break;
            case "down":
              currentTurtle.changePen(Pen.DOWN);
              break;
            default:
              currentTurtle.changeBrush(state.charAt(0));
              //Some single non blank character
              break;
          }
        } else {
          System.err.println("No such turtle with name '" + turtleName + "' exists");
        }
        break;
      case "move":
        //move name distance
        turtleName = cmds[1];
        int distance = Integer.parseInt(cmds[2]);
        
        //Do we have a turtle name turtleName already?
        if (turtles.containsKey(turtleName)) {
          
          //Move the turtle
          currentTurtle = turtles.get(turtleName);
          currentTurtle.move(distance);
          
        } else {
          System.err.println("No such turtle with name '" + turtleName + "' exists");
        }
        break;
      case "right":
      case "left":
        
        int angle = Integer.parseInt(cmds[2]);
        turtleName = cmds[1];
        currentTurtle = turtles.get(turtleName);

        if (turtles.containsKey(turtleName)) {
          //Rotate the turtle
          if (angle != 0 && angle % 45 == 0) {
            Rotation rotation = ("left".equals(cmds[0]) ? Rotation.LEFT : Rotation.RIGHT);
            currentTurtle.rotate(Direction.getDirectionFromAngle(angle), rotation, 1);
          } else {
            System.err.println("Incorect angle specified '" + angle + "'");
          }
        } else {
          System.err.println("No such turtle with name '" + turtleName + "' exists");
        }
        break;
      default:
        //show
        out.println(currentPaper.toString());
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
