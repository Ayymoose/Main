package interpreter;

import java.util.Arrays;
import java.util.Scanner;

public class Lexer {

    private Scanner scanner;
    
    //Constructor
    public Lexer(Scanner scanner) {  
      this.scanner = scanner;
    }
    
    //Gets the number of tokens in the current string 
    private int tokenCount(String string) {
     return string.split("\\s+").length;
    }
    
    //Returns a list of tokens 
    //TODO : Finish
    
    //Tokenises a single line of input returning the tokens ignoring white space and empty lines
    public String[] tokenise() {
    	
    //input -> process input -> clean input -> return 
    	
      
      String[] tokens = null;
      if (scanner != null) {
        
        if (scanner.hasNextLine()) {
          
          //Read a line of input
          String input = scanner.nextLine();

          //Get the total number of arguments passed in
          int numberOfTokens = tokenCount(input);

          if (numberOfTokens > 0) {
            tokens = new String[numberOfTokens];

            //Removes white space 
            tokens = input.split("\\s+"); 

            //System.out.println(Arrays.toString(tokens));
          }
          return tokens;
        }
        
        
        
      }
      return null;
    }
    
    
    
}