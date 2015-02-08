package interpreter;

public class Parser {
  
  //Parses tokens and returns a Function that contains the function name and arguments
  public Function parse(String[] tokens){ 
       
    Function function = new Function();
    String functionName = tokens[0];

    if (function.isFunction(functionName)) {
      if (function.canEvaluate(functionName, function.getArgumentsFromString(tokens))) {
        return new Function(functionName,function.getArgumentsAsString(tokens));            
      }
    } else {
      System.err.println("Cannot evaluate garbage '" + functionName + "'");
    }
    return null;
  }
  
}