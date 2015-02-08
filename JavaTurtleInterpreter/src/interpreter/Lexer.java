package interpreter;

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

  //Returns an array of tokens removing white spaces/lines
  public String[] tokenise() {

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
        }
        return tokens;
      }
    }
    return null;
  }
}