package turtle;

import java.io.FileNotFoundException;

import util.Direction;
import util.Pen;
import util.Rotation;


public class Main {

    public static void main(String[] args) throws FileNotFoundException {
      
      Coordinate position = new Coordinate(9,3);
      Paper p = new Paper(14,16);
      Direction d = Direction.NORTH_WEST;
      Turtle t = new Turtle(position, d, Pen.DOWN, p);
      
      t.changeBrush(' ');
      
      
      //p.write(new Coordinate(5,2), '#');
      //for (int i=0; i<3; i++) {
      //  d.rotate(Rotation.LEFT);
      //}
     
      
      // t.move(0);
      //t.rotate(Direction.NORTH_EAST, Rotation.LEFT, 3);
      //t.move(3);
      //t.rotate(Direction.EAST, Rotation.RIGHT, 2);
      //t.move(3);
      
      t.turtleStats();
      
      
      System.out.println(p.toString(t));
      //System.out.println("Width: " + p.getWidth() + " Height: " + p.getHeight());
      

      
      
      
      
      //Test cases
      
      
      //TestCases.Test.containsTest(p);
      
      
    }
}
