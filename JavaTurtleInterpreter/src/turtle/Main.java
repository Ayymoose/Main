package turtle;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;

public class Main {
  
    public static void main(String[] args) throws FileNotFoundException {
      
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
      turtleInterpreter.process(null,0);
    }
    
}
