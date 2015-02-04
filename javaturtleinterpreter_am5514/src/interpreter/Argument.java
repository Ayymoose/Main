package interpreter;

public enum Argument {
  
  INTEGER,
  STRING,
  KEYWORD;
  
  //ignore
  

  //Checks if the argument numbers match ; a bit silly and poorly design since the function name should be passed in aswell.
  public static boolean argumentNumberCheck(int expectedArguments,int actualArguments) {
    return expectedArguments == actualArguments;
  }
  
  //Compares whether the argument type matches via an array of arguments
  public static boolean argumentTypeCheck(Argument[] args1,Argument[] args2) {
    //Assuming that args1.length == args2.length
    
    for (int i=0; i<args1.length; i++) {
      if (!(args1[i] == args2[i])) {
        //System.out.println(args[i] + " != " + arguments[i]);
        return false;
      } else {
        //System.out.println(args[i] + " = " + arguments[i]);
      }
    }
    return true;
  }
  
}

