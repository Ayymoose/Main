package interpreter;

import interpreter.exceptions.InsufficientArgumentException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class Function {
  
  private String functionName;
  private String[] arguments;
  
  public Function(String functionName,String[] arguments) {
    this.functionName = functionName;
    this.arguments = arguments;
  }
  
  //Maps function names to overloaded arguments
  private final Map<String,Argument[][]> functionMap = new HashMap<String,Argument[][]>();
  //Contains keywords
  private final ArrayList<String> keywords = new ArrayList<String> ();
  
  //Defines a new function called functionName with parameter types given in arguments
  public void defineFunction(String functionName,Argument[][] arguments) {
    functionMap.put(functionName, arguments);
  }
  
  //Defines a keyword
  public void defineKeyword(String keyword) {
    keywords.add(keyword);
  }
  
  //Constructor
  public Function() {
    
    //new is overloaded
    defineFunction("new",new Argument[][] 
        { 
        new Argument[] {Argument.KEYWORD,Argument.STRING,Argument.INTEGER,Argument.INTEGER},
        new Argument[] {Argument.KEYWORD,Argument.STRING,Argument.INTEGER}
        });
    
    defineFunction("paper",new Argument[][] {
        new Argument[] {Argument.INTEGER,Argument.INTEGER}}
        );
    
    defineFunction("pen",new Argument[][] {
        new Argument[] {Argument.STRING,Argument.KEYWORD}}
        );
    
    defineFunction("move",new Argument[][] {
        new Argument[] {Argument.STRING,Argument.INTEGER}}
        );

    defineFunction("left",new Argument[][] {
        new Argument[] {Argument.STRING,Argument.INTEGER}}
        );
    
    defineFunction("right",new Argument[][] {
        new Argument[] {Argument.STRING,Argument.INTEGER}}
        );
    
    defineFunction("show",new Argument[][] {
        new Argument[] {Argument.NO_ARGUMENT}}
        );
    //
    defineKeyword("normal");
    defineKeyword("bouncy");
    defineKeyword("reflecting");
    defineKeyword("wrapping");
    defineKeyword("continuous");
    defineKeyword("cluster");
    defineKeyword("up");
    defineKeyword("down");
  }
  
  //Return the function name
  public String getFunctionName() {
    return functionName;
  }
  
  //Returns the number of arguments functionName has (index represents the overload index)
  public int getNumberOfArguments(String functionName,int index) {
    return (functionMap.get(functionName)[index][0] != Argument.NO_ARGUMENT ? functionMap.get(functionName)[index].length : 0);
  }
  
  //Returns an array of Argument for functionName ; (index represents the overload index)
  public Argument[] getFunctionArguments(String functionName,int index) {
    return functionMap.get(functionName)[index];
  }
  
  //Returns an array of Argument from tokens
  public Argument[] getArgumentsFromString(String[] tokens) {
    //Assuming the first argument is the function name
    return (tokens.length == 1 ? new Argument[] {Argument.NO_ARGUMENT} : stringsToArguments(Arrays.copyOfRange(tokens, 1, tokens.length)));
  }
 
  //Returns the arguments for the function
  public String[] getArgumentsAsString(String[] tokens) {
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

  //Returns the number of overloads a function has
  public int getNumberOfOverloads(String functionName) {
    return functionMap.get(functionName).length;
  }
  
  //Returns true iff the number of arguments matches that of the function functionName
  public boolean argumentNumberCheck(String functionName,int arguments) throws InsufficientArgumentException {
    //This function has to check all the overloads if they match
    int functionOverloads = getNumberOfOverloads(functionName);
    boolean result = false;
    
    //Match any
    for (int i=0; i<functionOverloads; i++) {
      result |= getNumberOfArguments(functionName,i) == arguments;
    }

    if (!result) {
      throw new InsufficientArgumentException("Too many/few arguments provided for function '" + functionName + "'");
    }
    return result;
  }
  
  //Returns true iff the arguments are exactly the same type as the function signature
  public boolean argumentTypeCheck(String functionName,Argument[] arguments) throws IllegalArgumentException{
    //Should output go to System?
    int functionOverloads = getNumberOfOverloads(functionName);
    boolean result = false;
    
    //Checks the entered signature against any/all overloads
    for (int i=0; i<functionOverloads; i++) {
      result |= Arrays.equals(getFunctionArguments(functionName,i),arguments);
    }
    
    if (!result) { 
      System.err.println("'" + functionName + "' expects method signature to match any of the following:");
      for (int i=0; i<functionOverloads; i++) {
        System.err.println(Arrays.deepToString(getFunctionArguments(functionName,i)));
      }
      System.err.println("But received " + Arrays.toString(arguments));
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
      return false;
    }
    return true;
  }
  
  //Return true iff the token is a function
  public boolean isFunction(String token) {
    return functionMap.containsKey(token);
  }
  
  //Returns true iff the token is a keyword
  //TODO: Fix ; a string will match a keyword or vice versa (Don't know how to fix?)
  public boolean isKeyword(String token) {
  //A keyword can also be a non blank character
    return keywords.contains(token) || token.matches("[^ ]");
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
