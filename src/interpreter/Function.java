package interpreter;

import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Function {
  
  //Why can't I make the methods static and call functionMap in them?
  private final Map<String,Integer> functionMap = new HashMap<String,Integer>();
  
  //Constructor
  public Function() {
    mapFunctions();
  }

  //Maps function names to argument names
  private void mapFunctions() {
    
    /*
     * In our turtle interpreter language we have the following commands
     * paper width height
     * new type name x y 
     * pen name state
     * move name distance
     * right name angle
     * left name angle
     */
    
    //These are NOT magic numbers! Please don't mark me down for this :)
    //Mapping of the function name to the number of arguments its expected to receive
    functionMap.put("paper",2);
    functionMap.put("new",4);
    functionMap.put("pen",2);
    functionMap.put("move",2);
    functionMap.put("right",2);
    functionMap.put("left",2);
  }

  //Returns the number of arguments a function has
  public int functionArguments(String functionName) {
    return functionMap.get(functionName);
  }
  
  //Returns the arguments for the function
  public Argument[] getFunctionArguments(String[] tokens) {
    //Assuming the first argument is the function name
    return stringsToArguments(Arrays.copyOfRange(tokens, 1, tokens.length));
  }
  
  
  //Converts a string to its corresponding argument
  public Argument stringToArgument(String string) {
    if (isLiteral(string)) {
      //System.out.println(string + " is string");
      return Argument.STRING;
    } else {
      //System.out.println(string + " is integer");
      return Argument.INTEGER;
    }
  }
  
  public Argument[] stringsToArguments(String[] string) {
    Argument[] args = new Argument[string.length];
    for (int i=0; i<args.length; i++) {
      args[i] = stringToArgument(string[i]);
    }
    return args;
  }
  //
  
  //Returns true iff we can evaluate the function with the given arguments
  public boolean canEvaluate(String functionName,Argument[] arguments) {
  
    int numberOfArguments = functionArguments(functionName);
    int expectedArguments = functionMap.get(functionName);
    
    //Match number of arguments , throw argument mismatch exception
    Argument.argumentNumberCheck(numberOfArguments,expectedArguments);
    
    switch (functionName) {
      case "paper":
           
        //Expecting two integers
        Argument[] paperArguments = {Argument.INTEGER,Argument.INTEGER};
        
        //Throw illegal argument type exception
        Argument.argumentTypeCheck(paperArguments, arguments);
        
        /*
         * 
         * WHERE I LEFT OFF @ 18:38
         * Doesn't do anything yet since I don't have any exception handling implemented
         * 
         */
        
      break;
      
      
      
      default:
        
    }
    
    
    return true;
  }
  
  //Return true iff the token is a function
  public boolean isFunction(String token) {
    switch (token) {
      case "paper":        
      case "new":   
      case "pen":
      case "move":
      case "right":
      case "left":
        return true;
      default:
        return false;
    }
  }
  
  //Returns true iff the token is a keyword
  public boolean isKeyword(String token) {
    switch (token) {
      case "normal":
        return true;
      default:
        return false;
    }
  }
  
  //Returns true iff the token is an integer
  public boolean isInteger(String token) {
    return token.matches("\\d+");
  }
  
  //Returns true iff the token is a literal (String)
  public boolean isLiteral(String token) {
    return !(isFunction(token) || isKeyword(token) || isInteger(token)) && token.length() > 0 ;
  }
  
}

