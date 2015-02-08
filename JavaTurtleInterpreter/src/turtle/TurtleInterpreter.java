package turtle;

import interpreter.Function;
import interpreter.Lexer;
import interpreter.Parser;

import java.io.InputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import turtle.implementations.AbstractTurtle;
import turtle.implementations.BouncyTurtle;
import turtle.implementations.ClusterTurtle;
import turtle.implementations.ContinuousTurtle;
import turtle.implementations.NormalTurtle;
import turtle.implementations.ReflectingTurtle;
import turtle.implementations.WrappingTurtle;
import util.Direction;
import util.Pen;
import util.Rotation;

public class TurtleInterpreter {
 
  private InputStream in;
  private PrintStream out;
  private Paper currentPaper = new Paper(10,10);
  private String turtleName;
  private final Map<String,AbstractTurtle> turtles = new HashMap<String, AbstractTurtle>();
  private String clusterName= null;
  
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
  
  public void evaluate(String functionName,String[] arguments) {
    
    //User defined implementation goes here
    switch (functionName) {
      case "paper":
        int width = Integer.parseInt(arguments[0]);
        int height = Integer.parseInt(arguments[1]);
        currentPaper = new Paper(width,height);
      break;
      case "new":
        String type = arguments[0];
        Coordinate coordinate = null;
        //AbstractTurtle[] cluster = null;
        
        
        
        if (type.equals("cluster")) {
          
          int functionCalls = Integer.parseInt(arguments[2]);
          clusterName = arguments[1];
          
          //Creates an array of turtles passed to cluster
          //cluster = new AbstractTurtle[functionCalls];
          
      
          //System.out.println("Cluster called");
          
          
          process("new",functionCalls);
          
          
          
        } else {
          turtleName = arguments[1];
          coordinate = new Coordinate(Integer.parseInt(arguments[2]),Integer.parseInt(arguments[3]));  
        }
        switch (type) {
          case "normal":
            if (clusterName == null) {
              turtles.put(turtleName, new NormalTurtle(currentPaper,coordinate));
            } else {
              turtles.put(clusterName + "." + turtleName, new NormalTurtle(currentPaper,coordinate));
              System.out.println(turtles.toString());
              
            }
            break;
          case "bouncy":
            turtles.put(turtleName,new BouncyTurtle(currentPaper,coordinate));
            break;
          case "reflecting":
            turtles.put(turtleName,new ReflectingTurtle(currentPaper,coordinate));
            break;
          case "continuous":
            turtles.put(turtleName,new ContinuousTurtle(currentPaper,coordinate));
            break; 
          case "wrapping":
            turtles.put(turtleName,new WrappingTurtle(currentPaper,coordinate));
            break;
          //case "cluster":
          //  turtles.put(turtleName,new ClusterTurtle(cluster));
          //  break;
        }
        break;
      case "pen":
        turtleName = arguments[0];
        if (turtles.containsKey(turtleName)) {
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
        } else {
          System.err.println("No instance of turtle '" + turtleName + "' exists!");
        }
        break;
      case "move":
        turtleName = arguments[0];
        if (turtles.containsKey(turtleName)) {
          int distance = Integer.parseInt(arguments[1]);
          turtles.get(turtleName).move(distance);
        } else {
          System.err.println("No instance of turtle '" + turtleName + "' exists!");
        }
        break;
      case "right":
      case "left":
        turtleName = arguments[0];
        if (turtles.containsKey(turtleName)) {
          int angle = Integer.parseInt(arguments[1]); 
          if (angle % 45 == 0 && angle !=0) {
            Rotation rotation = (functionName.equals("left") ? Rotation.LEFT : Rotation.RIGHT);
            turtles.get(turtleName).rotate(angle, rotation, angle / 45);
          } else {
            System.err.println("angle must be a multiple of 45 and non-zero.");
          }
        } else {
          System.err.println("No instance of turtle '" + turtleName + "' exists!");
        }
        break;
      case "show":
        out.println(currentPaper.toString());
        break;
      default: 
        //
        break;
    }
  }
  
  //Processes input from an InputStream and writes the output to an PrintStream out
  public void process(String functionName,int calls) {
  
    //Lexically analyse the input and split into tokens
    Lexer lexer = new Lexer(new Scanner(in));  
    String[] tokens;
    Parser parser = new Parser();   
    
    
    
    //Override this method
    if (functionName != null && calls > 0) {
      int functionCalls = calls;

      //So we expect functionName to called calls times
      while ((tokens = lexer.tokenise()) != null) {
        
        Function f = parser.parse(tokens);
        //System.out.println("functionCalls = " + functionCalls + " and f is null? = " + (f == null));
        while (functionCalls>0 && f != null) {
          if (f.getFunctionName().equals(functionName)) {
            functionCalls--;
            //System.out.println(functionCalls + " calls remaining.");
            evaluate(functionName,f.getArgumentsAsString(tokens));
            process(functionName,functionCalls);
          } else {
            System.err.println("Expecting function '" + functionName + "' to be called for cluster.");
            System.err.println("Received: '" + f.getFunctionName() + "'");
            break;
          }
        } 
        
        //System.out.println("While loop terminated");
        
      }
    } else {
      //System.out.println("Main process started");
      clusterName = null;
      while ((tokens = lexer.tokenise()) != null) {
        //Get the function (if any)
        Function function = parser.parse(tokens);
        if (function != null) {
          evaluate(function.getFunctionName(),function.getArgumentsAsString(tokens));
        }
      } 
      System.out.println("Null input received -> Program terminated");
    }
    
    
    
    
  }
  

}
