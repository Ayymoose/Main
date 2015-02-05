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
    
    //Tokenises the input to give back a list of tokens to be passed to the parser
    //Returns a list of tokens
    public String[] tokenise(String delimiter) {
      
      String[] tokens = null;
      if (scanner != null) {
        
        if (scanner.hasNextLine()) {
          
          //Read a line of input
          String input = scanner.nextLine();

          //Get the total number of arguments passed in
          int numberOfTokens = tokenCount(input,delimiter);

          if (numberOfTokens > 0) {
            //Populate the array with whatever input we are fed
            tokens = new String[numberOfTokens];
            //Easy tokenising by using split!
            tokens = input.split(delimiter); 
           
          }
          return tokens;
        }
      }
      return null;
    }

}