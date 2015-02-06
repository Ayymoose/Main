package interpreter;

import java.util.ArrayList;

public class Parser {
  
  //Parses the tokens and returns true if it was successful
  public ArrayList<Function> parse(String[] tokens){ 
    ArrayList<Function> functionList = new ArrayList<Function>();      
    Function function = new Function();
    
    //Input expected
    //function [argument1,argument2...argumentn]
    
    String functionName = tokens[0];
    
    //System.out.println(function.getNumberOfArguments(functionName));

    if (function.isFunction(functionName)) {
      //If the function can be evaluated then add it to the function list
      if (function.canEvaluate(functionName, function.getFunctionArguments(tokens))) {
        functionList.add(new Function(functionName,function.getFunctionArgumentsAsString(tokens)));            
      }
    }

    
    
    return functionList; 
  }
}