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
  
  
  
}
