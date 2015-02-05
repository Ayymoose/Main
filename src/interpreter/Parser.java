package interpreter;

import java.util.ArrayList;

public class Parser {
  
  //Default constructor
  public Parser() {};
  
  //Parses the tokens and returns true if it was successful
  //TODO: Finish
  public ArrayList<Function> parse(String[] tokens) {
    
    //Expects a function first
    if (tokens != null) {      
      
      Function function = new Function();
      
      ArrayList<Function> functionList = new ArrayList<Function>();

      for (String token : tokens) {
        
        if (function.isFunction(token)) {
          if (function.canEvaluate(token, function.getFunctionArguments(tokens))) {
            
            functionList.add(new Function(token,function.getFunctionArgumentsAsString(tokens)));            

          } else {
            return null;
          }
        } else if (function.isKeyword(token)) {
          System.err.println("Cannot evaluate KEYWORD '" + token + "'");
        } else if (function.isInteger(token)) {
          System.err.println("Cannot evaluate INTEGER '" + token + "'");
        } else if (function.isLiteral(token)) {
          System.err.println("Cannot evaluate LITERAL '" + token + "'");
        } else {
          System.err.println("Cannot evaluate garbage '" + token + "'");
        }

      }
      return functionList;
    } 
    return null;
  }
}
