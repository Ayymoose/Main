package interpreter;

import interpreter.exceptions.InsufficientArgumentException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Function {
  
  public String toString() {
    return "FUNCTION NAME '" + functionName + "' ARGUMENTS: " + Arrays.toString(arguments);
  }
  
  private String functionName;
  private String[] arguments;
  
  public Function(String functionName,String[] arguments) {
    this.functionName = functionName;
    this.arguments = arguments;
  }
  
  //Maps function names to arguments
  private final Map<String,Argument[]> functionMap = new HashMap<String,Argument[]>();
  //Contains keywords
  private final ArrayList<String> keywords = new ArrayList<String> ();
  //Types
  private final ArrayList<String> types = new ArrayList<String> ();
  
  
  //Defines a new function called functionName with parameter types given in arguments
  public void defineFunction(String functionName,Argument[] arguments) {
    functionMap.put(functionName, arguments);
  }
  
  public void defineKeyword(String keyword) {
    keywords.add(keyword);
  }
  
  public void defineType(String type) {
    types.add(type);
  }

  //Constructor
  public Function() {
    defineFunction("paper",new Argument[] {Argument.INTEGER,Argument.INTEGER});
    defineFunction("new",new Argument[] {Argument.KEYWORD,Argument.STRING,Argument.INTEGER,Argument.INTEGER});
    defineFunction("pen",new Argument[] {Argument.STRING,Argument.KEYWORD});
    defineFunction("move",new Argument[] {Argument.STRING,Argument.INTEGER});
    defineFunction("left",new Argument[] {Argument.STRING,Argument.INTEGER});
    defineFunction("right",new Argument[] {Argument.STRING,Argument.INTEGER});
    defineFunction("show",new Argument[] {Argument.NO_ARGUMENT});
    //
    defineKeyword("normal");
    defineKeyword("up");
    defineKeyword("down");
  }
  
  //Return the function name
  public String getFunctionName() {
    return functionName;
  }
  
  //Returns the number of arguments a function has
  public int getNumberOfArguments(String functionName) {
    
    return (functionMap.get(functionName)[0] != Argument.NO_ARGUMENT ? functionMap.get(functionName).length : 0);
    
   // return functionMap.get(functionName).length;
  }
  
  //Returns the arguments for the function as Argument[]
  public Argument[] getFunctionArguments(String[] tokens) {
    //Assuming the first argument is the function name
    return (tokens.length == 1 ? new Argument[] {Argument.NO_ARGUMENT} : stringsToArguments(Arrays.copyOfRange(tokens, 1, tokens.length)));
    
    //return stringsToArguments(Arrays.copyOfRange(tokens, 1, tokens.length));
  }
  
  //Returns the arguments for the function
  public String[] getFunctionArgumentsAsString(String[] tokens) {
    //Assuming the first argument is the function name
    return Arrays.copyOfRange(tokens, 1, tokens.length);
  }
  
  //Converts a string to its corresponding argument
  public Argument stringToArgument(String string) {
    if (isLiteral(string)) {
      return Argument.STRING;
    } else if (isInteger(string)){
      return Argument.INTEGER;
    } else if (isKeyword(string)){
      return Argument.KEYWORD;
    } else {
      return Argument.NO_ARGUMENT;
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
    boolean result = getNumberOfArguments(functionName) == arguments;
    if (!result) {
      throw new InsufficientArgumentException("Expecting " + getNumberOfArguments(functionName) + " argument(s) but received " + arguments + " for function '" + functionName + "'");
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
      argumentNumberCheck(functionName,(arguments.length == 1 ? 0 : arguments.length));
      argumentTypeCheck(functionName,arguments);
    } catch (InsufficientArgumentException iae) {
      System.err.println(iae.getMessage());
      System.exit(-1);
      return false;
    } catch (IllegalArgumentException iae) {
      System.err.println(iae.getMessage());
      System.exit(-1);
      return false;
    }
    return true;
  }
  
  //Return true iff the token is a function
  public boolean isFunction(String token) {
    return functionMap.containsKey(token);
  }
  
  //Returns true iff the token is a keyword
  public boolean isKeyword(String token) {
  //A keyword can also be a non blank character
    return keywords.contains(token) || token.matches("^ .");
  }
  
  //Returns true iff the token is an integer
  public boolean isInteger(String token) {
    return token.matches("\\d+");
  }
  
  //Returns true iff the token is a literal (String)
  public boolean isLiteral(String token) {
    return !(isFunction(token) || isKeyword(token) || isInteger(token)) && token.length() > 0 ;
  }
  
  //Returns true iff the token is a type
  public boolean isType(String token) {
    return types.contains(token);
  }
}
