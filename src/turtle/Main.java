package turtle;

import interpreter.Lexer;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Arrays;
//import java.util.Arrays;
//import java.util.Scanner;


public class Main {
  

  /*
   * The main method should check the program’s arguments to see where the input should be
     read from and where the output should be written to. 
     
     It should also create the appropriate
     Scanner and PrintStream instances. It should then create a new TurtleInterpreter, and use the
     aforementioned public method to process the commands in the input.
   */

    public static void main(String[] args) throws FileNotFoundException {
      
      
     /*
        Your program will be invoked with zero, one or two command-line arguments. The first argument
        (if present) will specify the name of a file where the Turtle Graphics Language commands are to
        be read from. If there are no arguments, you should assume that the commands are to be read
        from standard input. The second argument, if present, will specify a file to which the output of
        show should be written. If there is no second argument, then show should output to standard
        output.
      */
      
      //Function f = new Function();
      //System.out.println(f.isKeyword("#"));
      
      //Lexer l = new Lexer(new Scanner(System.in));
      
     // String[] s = {"test"," ","abc"," "};
      //System.out.println(Arrays.toString(l.removeSpace(s)));
    /*
      String s = "new bouncy  maeve 0 12";
      String[] p = s.split("\\s+");
      
      System.out.println(Arrays.toString(p));
      */
      
      TurtleInterpreter turtleInterpreter = new TurtleInterpreter();
      
      int numberOfArguments = args.length;
      String inputFileName;
      String outputFileName;
      
      switch (numberOfArguments) {
        case 0:
          turtleInterpreter.updateStream(System.in, System.out);
          break;
        case 1:
          inputFileName = args[0];
          turtleInterpreter.updateStream(new FileInputStream(inputFileName), System.out);
          break;
        case 2:
          inputFileName = args[0];
          outputFileName = args[1];
          turtleInterpreter.updateStream(new FileInputStream(inputFileName), new PrintStream(new File(outputFileName)));
          break;
        default:
          System.err.println("Garbage input received.");
          System.exit(-1);
        break;    
      }
      turtleInterpreter.process();
      
      
    }
    
}
