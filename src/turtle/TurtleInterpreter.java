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

public class TurtleInterpreter {
  
  /*
     The interpreter part of your program should not see the tokens (and certainly never the raw input). 
     Instead it should be told what methods to execute and what values those methods parameters have.
     
     A TurtleInterpreter is responsible for managing the mapping of turtle names to turtle instances,
     keeping track of the current paper, and knowing where to read input from and to send output to.
   */
  
  private final Map<String,Turtle> turtles = new HashMap<String, Turtle>();


  
  //Processes input from an InputStream and writes the output to an OutputStream out
  public void process(InputStream in,PrintStream out) {
  
    //Lexically analyse the input and split into tokens
    Lexer lexer = new Lexer(new Scanner(in));   
    String[] tokens = lexer.tokenise(" ");
    
    //Parses the input and tells the turtleInterpreter what functions it needs to evaluate
    Parser parser = new Parser();       
    ArrayList<Function> functions = parser.parse(tokens);
    
    if (functions == null) {
      System.err.println("No functions to evaluate!");
    } else {
      
      //Evaluate each function
      for (int i=0; i<functions.size(); i++) {
        Function f = functions.get(i);
        //System.out.println(f.toString());
        f.evalute(f.getFunctionName(),f.getFunctionArgumentsAsString(tokens));
      }
    }
  }
}
