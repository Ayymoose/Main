package turtle;

import interpreter.Function;
import interpreter.Lexer;
import interpreter.Parser;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import util.Direction;
import util.Pen;
import util.Rotation;

public class TurtleInterpreter {
  
  /*
     The interpreter part of your program should not see the tokens (and certainly never the raw input). 
     Instead it should be told what methods to execute and what values those methods parameters have.
     
     A TurtleInterpreter is responsible for managing the mapping of turtle names to turtle instances,
     keeping track of the current paper, and knowing where to read input from and to send output to.
   */
  
  private InputStream in;
  private PrintStream out;
  private Paper currentPaper = new Paper(10,10);
  private String turtleName;
  
  //Constructor
  public TurtleInterpreter(InputStream in,PrintStream out) {
    this.in = in;
    this.out = out;
  }
  
  //Default
  public TurtleInterpreter() {};
  
  
  public void updateStream(InputStream in,PrintStream out) {
    this.in = in;
    this.out = out;
  }
  
  private final Map<String,Turtle> turtles = new HashMap<String, Turtle>();


  public void evaluate(String functionName,String[] arguments) {
    
    //paper ["10","10"]
    //new ["normal","turtle1","3","4"]
    
  
    

  
    
    //This is exactly what I was trying to avoid but I can't think of a nice way
    //to implement this sort of thing
    //"Hardcoding" arguments
    //What is the correct way to handle this sort of thing?
    
    //User defined implementation goes here
    switch (functionName) {
      case "paper":
        int width = Integer.parseInt(arguments[0]);
        int height = Integer.parseInt(arguments[1]);
        currentPaper = new Paper(width,height);
      break;
      
      case "new":
        
        String type = arguments[0];
        turtleName = arguments[1];
        int x = Integer.parseInt(arguments[2]);
        int y = Integer.parseInt(arguments[3]);
        Coordinate position = new Coordinate(x,y);  
        
        Turtle turtle = new Turtle(position,Direction.NORTH,Pen.UP,currentPaper);
        turtles.put(turtleName, turtle);
        turtle.changeBrush('*');
        
        /*
        switch (type) {
          case "normal":
             
            break;
            
          default:
            //
            break;
        }*/
        
        break;
      case "pen":
        
        turtleName = arguments[0];
        String state = arguments[1];
        
        switch (state) {
        case "up":
          turtles.get(turtleName).changePen(Pen.UP);
          break;
        case "down":
          turtles.get(turtleName).changePen(Pen.DOWN);
          break;  
        default:
          turtles.get(turtleName).changeBrush(state.charAt(0));
          break;
        }
        
        break;
      case "move":
        
        turtleName = arguments[0];
        int distance = Integer.parseInt(arguments[1]);
        turtles.get(turtleName).move(distance);
        break;
        
      case "right":
      case "left":
        
        turtleName = arguments[0];
        int angle = Integer.parseInt(arguments[1]); // angle % 45 = 0 and angle != 0
 
        Rotation rotation = (functionName.equals("left") ? Rotation.LEFT : Rotation.RIGHT);
        //System.out.printf("rotation=%S angle=%d angle/45=%d",rotation,angle,angle/45);
        //System.out.println();
        turtles.get(turtleName).rotate(angle, rotation, angle / 45);
        
        
        break;
      case "show":
        //If currentPaper is not null
        out.println(currentPaper.toString());
        break;
      default: 
        //
        break;
        
    }
    

    
  }
  
  //Processes input from an InputStream and writes the output to an PrintStream out
  public void process() {
  
    //Lexically analyse the input and split into tokens
    Lexer lexer = new Lexer(new Scanner(in));  
    String[] tokens;
    Parser parser = new Parser();   

    while ((tokens = lexer.tokenise()) != null) {
      
      ArrayList<Function> functions = parser.parse(tokens);
      /*
      if (functions.isEmpty()) {
        System.err.println("No functions to evaluate!");
      } else {*/
        //Evaluate each function
        for (int i=0; i<functions.size(); i++) {
          Function function = functions.get(i);
          //System.out.println(f.toString());
          evaluate(function.getFunctionName(),function.getFunctionArgumentsAsString(tokens));
        }
      //}
      
    }
    
    
  }
}
