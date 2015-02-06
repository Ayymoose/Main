package interpreter;

import java.util.Scanner;

public class Lexer {

    private Scanner scanner;
    
    //Constructor
    public Lexer(Scanner scanner) {  
      this.scanner = scanner;
    }
    
    //Gets the number of tokens in the current string 
    private int tokenCount(String string,String delimiter) {
     return string.split(delimiter).length;
    }
    
    //Returns a list of tokens , should ignore white space 
    public String[] tokenise(String delimiter) {
      
      String[] tokens = null;
      if (scanner != null) {
        
        if (scanner.hasNextLine()) {
          
          //Read a line of input
          String input = scanner.nextLine();

          //Get the total number of arguments passed in
          int numberOfTokens = tokenCount(input,delimiter);

          if (numberOfTokens > 0) {
            tokens = new String[numberOfTokens];
            tokens = input.split(delimiter); 
          }
          return tokens;
        }
        
        
        
      }
      return null;
    }

}