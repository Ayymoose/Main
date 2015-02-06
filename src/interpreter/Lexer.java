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

            //System.out.println(Arrays.toString(tokens));
          }
          return tokens;
        }
        
        
        
      }
      return null;
    }
    
/*
    private String[] removeSpace(String[] strings) {
      
      int size = strings.length;
      int count = 0;
      
      for(String string : strings) {
        if (string.equals(" ")) {
          count++;
        }
      }
      
      String[] newString = new String[size - count];
      for (int i=0,j=0; i<size; i++) {
        if (!strings[i].equals(" ")) {
          newString[j] = strings[i];
          j++;
        } 
        //{"test" , }
        //{"test"," ","abc"," "}; 
          
        //?( )\w 
        
      }
      
      return newString;
      
    }*/
    
    
}