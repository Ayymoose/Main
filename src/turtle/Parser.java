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

  public String[] parse() {
    
    /*
     * Validates the array to match the arguments of the command
     * Does not modify the array
     */
    
    String[] tokens = null;
    
    //Assuming that scanner is NOT null
    while (scanner.hasNextLine()) {
      
      //Read a line of input
      String input = scanner.nextLine();
      
      //Get the total number of arguments passed in
      int numberOfTokens = tokenCount(input);
      
      if (numberOfTokens > 0) {
        //Populate the array with whatever input we are fed
        tokens = new String[numberOfTokens];
        tokens = input.split(" ");
        
        
        
        
        
        
        
        
        
       }
    
    }
    
    return tokens;
  }
}
