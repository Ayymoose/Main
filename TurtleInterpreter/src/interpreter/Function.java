package interpreter;

import interpreter.exceptions.InsufficientArgumentException;

import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Function {
  
  //Maps function names to arguments
  private final Map<String,Argument[]> functionMap = new HashMap<String,Argument[]>();
   
  //Defines a new function called functionName with parameter types given in arguments
  public void createFunction(String functionName,Argument[] arguments) {
    functionMap.put(functionName, arguments);
  }
  
  //Constructor
  public Function() {
    createFunction("paper",new Argument[] {Argument.INTEGER,Argument.INTEGER});
    createFunction("new",new Argument[] {Argument.KEYWORD,Argument.STRING,Argument.INTEGER,Argument.INTEGER});
    createFunction("pen",new Argument[] {Argument.STRING,Argument.KEYWORD});
    createFunction("move",new Argument[] {Argument.STRING,Argument.INTEGER});
    createFunction("left",new Argument[] {Argument.STRING,Argument.INTEGER});
    createFunction("right",new Argument[] {Argument.STRING,Argument.INTEGER});
  }

  //Returns the number of arguments a function has
  public int functionArgumentCount(String functionName) {
    return functionMap.get(functionName).length;
  }
  
  //Returns the arguments for the function
  public Argument[] getFunctionArguments(String[] tokens) {
    //Assuming the first argument is the function name
    return stringsToArguments(Arrays.copyOfRange(tokens, 1, tokens.length));
  }
  
  //Converts a string to its corresponding argument
  public Argument stringToArgument(String string) {
    if (isLiteral(string)) {
      return Argument.STRING;
    } else if (isInteger(string)){
      return Argument.INTEGER;
    } else {
      return Argument.KEYWORD;
    }
  }
  
  public Argument[] stringsToArguments(String[] string) {
    Argument[] args = new Argument[string.length];
    for (int i=0; i<args.length; i++) {
      args[i] = stringToArgument(string[i]);
    }
    return args;
  }
  
  //Returns true iff the number of arguments matches that of the function functionName
  public boolean argumentNumberCheck(String functionName,int arguments) throws InsufficientArgumentException {
    boolean result = functionMap.get(functionName).length == arguments;
    if (!result) {
      throw new InsufficientArgumentException("Expecting " + functionMap.get(functionName).length + " argument(s) but only received " + arguments + " for function '" + functionName + "'");
    }
    return result;
  }
  
  //Returns true iff the arguments are exactly the same type as the function signature
  public boolean argumentTypeCheck(String functionName,Argument[] arguments) throws IllegalArgumentException{
    boolean result = Arrays.equals(functionMap.get(functionName), arguments);
    if (!result) { 
      throw new IllegalArgumentException("Arguments provided do not match the method signature for '" + functionName + "'");
    }
    return result;
  }
  
  //Returns true iff we can evaluate the function functionName with the given arguments
  public boolean canEvaluate(String functionName,Argument[] arguments)  {
    try {
      argumentNumberCheck(functionName,arguments.length);
      argumentTypeCheck(functionName,arguments);
    } catch (InsufficientArgumentException iae) {
      System.err.println(iae.getMessage());
      return false;
    } catch (IllegalArgumentException iae) {
      System.err.println(iae.getMessage());
      return false;
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
      //case "up":    //Might have to split these into types later on
     // case "down":
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
