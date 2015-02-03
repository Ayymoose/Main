package TestCases;
import turtle.Coordinate;
import turtle.Paper;

public class Test {

  
  public static void containsTest(Paper paper) {
    
    //contains(x,y)
    assert(paper.contains(0, 0) == true);
    assert(paper.contains(paper.getWidth(), paper.getHeight()) == false);
    assert(paper.contains(paper.getWidth(), 0)) == false;
    assert(paper.contains(0, paper.getHeight()-1) == true);
    assert(paper.contains(paper.getWidth()-1, paper.getHeight()-1) == true);
    //contains(Coordinate c)
    assert(paper.contains(new Coordinate(0,0)) == true);
    assert(paper.contains(new Coordinate(paper.getWidth(), paper.getHeight())) == false);
    assert(paper.contains(new Coordinate(paper.getWidth(), 0))) == false;
    assert(paper.contains(new Coordinate(0, paper.getHeight()-1)) == true);
    assert(paper.contains(new Coordinate(paper.getWidth()-1, paper.getHeight()-1)) == true);
  }

 // public static void 
  
  
  /*
  
  //Process
  switch (cmds[0]) {
    case "paper":
      if (numberOfTokens == 3) {
        if (!(cmds[1].matches("\\d+") || cmds[2].matches("\\d+"))) {
          System.err.println("Expecting an integer for x or y but received garbage");
          cmds = null;
        }
      } else {
        System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    case "new":
      if (numberOfTokens == 5) {
        if (!(cmds[3].matches("\\d+") || cmds[4].matches("\\d+"))) {
          System.err.println("Expecting an integer for x or y but received garbage");
          cmds = null;
        }
      } else {
        System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    case "pen":
      if (numberOfTokens == 3) {
          if (!cmds[2].matches("up|down|.")) {
            System.err.println("Expecting 'up' or 'down' or a single character but received garbage");
            cmds = null;
        }
      } else {
        System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    case "move":
      if (numberOfTokens == 3) {
        if (!cmds[2].matches("\\d+")) {
          System.err.println("Expecting 'up' or 'down' or a single character but received garbage");
          cmds = null;
        }
      } else {
        System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    case "right":
    case "left":
      if (numberOfTokens == 3) {
        if (!cmds[2].matches("\\d+")) {
          System.err.println("Expecting an integer for angle but received garbage");
          cmds = null;
        }
      } else {
        System.err.println("Expecting an 3 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    case "show":
      if (numberOfTokens != 1) { 
        System.err.println("Expecting an 1 argument(s) but received " + numberOfTokens);
        cmds = null;
      }
      break;
    default:
      System.err.println("You entered some garbage! How am I supposed to process that?! >.<");
      break;
  }
} else {
  System.err.println("You entered some garbage! What am I supposed to do?! >.<");
}
*/
  
  
}
