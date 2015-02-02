package turtle;

import java.util.Scanner;


public class Parser {
  
  
  private Scanner scanner;
  
  //Constructor
  public Parser(Scanner scanner) {  
    this.scanner = scanner;
  }
  
  //Gets the number of tokens in the current string
  //Assuming that the delimter is ' '
  private int tokenCount(String string) {
   return string.split(" ").length;
  }
  
  //Parses the input and returns to the TurtleInterpreter what methods it should call with the respective arguments
  public String[] parse() {
    
    String[] cmds = null;
    
    //Assuming that scanner is NOT null
    while (scanner.hasNextLine()) {
      //Read a line of input
      String input = scanner.nextLine();
      
      int numberOfTokens = tokenCount(input);
      
      if (numberOfTokens > 0) {
        
        //Populate the array with whatever input we are fed
        cmds = new String[numberOfTokens];
        cmds = input.split(" ");
        
        //Process
        switch (cmds[0]) {
          case "paper":
            if (numberOfTokens == 3) {
              try {
                //Will throw an exception on garbage
                Integer.parseInt(cmds[1]); 
                Integer.parseInt(cmds[2]);
              } catch (NumberFormatException nfe) {
                cmds = null;
                System.err.println("Expecting an integer for width or height but received garbage");
              }
            } else {
              cmds = null;
              System.err.println("Expecting 3 arguments");
            }
            break;
          case "new":
            break;
          case "pen":
          
            break;
          case "move":
            break;
          case "right":
            break;
          case "show":
           
            break;
            
          default:
            System.err.println("You entered some garbage!");
            //Throw some exception?
            break;
            
        }
        
      } else {
        System.err.println("Garbage entered");
      }

      
      break;
      
    }
    
    return cmds;
    
    
  }
  
  
  

}
