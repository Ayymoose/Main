package interpreter;

public class Parser {
  
  //Parses tokens and returns a Function that contains the function name and arguments
  public Function parse(String[] tokens){ 
       
    Function function = new Function();
    String functionName = tokens[0];
    
    //If this is command line then print the errors
    //Otherwise print the errors at the line number of the file
    
    //new cluster cluster_name n
    //The next n lines should be new commands

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