package turtle;

import java.util.Scanner;


public class Parser {
  
  
  private Scanner scanner;
  
  //Constructor
  public Parser(Scanner scanner) {  
    this.scanner = scanner;
  }
  
  //Gets the number of tokens in the current string
  //Assuming that the delimiter is ' '
  private int tokenCount(String string) {
   return string.split(" ").length;
  }
  
  //Parses the input and returns to the TurtleInterpreter what methods it should call with the respective arguments
  //Ugly messy code
  //Don't know how to create/throw custom exceptions yet
  public String[] parse() {
    
    /*
     * Validates the array to match the arguments of the command
     * Does not modify the array
     */
    
    String[] cmds = null;
    
    //Assuming that scanner is NOT null
    while (scanner.hasNextLine()) {
      
      //Read a line of input
      String input = scanner.nextLine();
      
      //Get the total number of arguments passed in
      int numberOfTokens = tokenCount(input);
      
      if (numberOfTokens > 0) {
        
        //Populate the array with whatever input we are fed
        cmds = new String[numberOfTokens];
        cmds = input.split(" ");
        
        //Process
        switch (cmds[0]) {
          case "paper":
            if (numberOfTokens == 3) {
              if (!(cmds[1].matches("\\d+") || cmds[2].matches("\\d+"))) {
                System.err.println("Expecting an integer for x or y but received garbage");
                cmds = null;
              }
            } else {
              System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          case "new":
            if (numberOfTokens == 5) {
              if (!(cmds[3].matches("\\d+") || cmds[4].matches("\\d+"))) {
                System.err.println("Expecting an integer for x or y but received garbage");
                cmds = null;
              }
            } else {
              System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          case "pen":
            if (numberOfTokens == 3) {
                if (!cmds[2].matches("up|down|.")) {
                  System.err.println("Expecting 'up' or 'down' or a single character but received garbage");
                  cmds = null;
              }
            } else {
              System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          case "move":
            if (numberOfTokens == 3) {
              if (!cmds[2].matches("\\d+")) {
                System.err.println("Expecting 'up' or 'down' or a single character but received garbage");
                cmds = null;
              }
            } else {
              System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          case "right":
          case "left":
            if (numberOfTokens == 3) {
              if (!cmds[2].matches("\\d+")) {
                System.err.println("Expecting an integer for angle but received garbage");
                cmds = null;
              }
            } else {
              System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          case "show":
            if (numberOfTokens != 1) { 
              System.err.println("Expecting an 1 argument(s) but received " + numberOfTokens);
              cmds = null;
            }
            break;
          default:
            System.err.println("You entered some garbage! How am I supposed to process that?! >.<");
            //Throw some exception?
            break;
        }
      } else {
        System.err.println("You entered some garbage! What am I supposed to do?! >.<");
      }
      break;
    }
    return cmds;
  }
}
