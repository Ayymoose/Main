package interpreter;

public class Parser {
  
  //Default constructor
  public Parser() {};
  
  //Parses tokens passed in
  public void parser(String[] tokens) {
    
    
    Function function = new Function();
    
    for (String token : tokens) {
      
      if (function.isFunction(token)) {
        
        //Check if we can evaluate the function
    
        
        
        //tokens is everything including the function name!
        if (function.canEvaluate(token,function.getFunctionArguments(tokens))) {
          
          //We can evaluate the function
          
          System.out.println("test OK");
        }
        
        //paper 10 10
        
        
        //System.out.println("'" + token + "' is a FUNCTION");
      } else if (function.isKeyword(token)) {
        //System.out.println("'" + token + "' is a KEYWORD");
      } else if (function.isInteger(token)) {
        //System.out.println("'" + token + "' is a INTEGER");
      } else if (function.isLiteral(token)) {
        //System.out.println("'" + token + "' is a LITERAL");
      } else {
        //System.out.println("'" + token + "' is GARBAGE");
      }
      
      
      
      
    }
    
    //Evaluate the token
    //Is it a function
    //Is it a keyword
    //Is it a integer
    //Or is it garbage
    
    //Allowed tokens are from the set
    //{function,keyword,integer}
    //Anything else defaults to garbage
    

    
    
    
    
    
    
  }
  
  

}
