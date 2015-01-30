package turtle;

import java.io.FileNotFoundException;

import util.Direction;
import util.Pen;
import util.Rotation;


public class Main {

    public static void main(String[] args) throws FileNotFoundException {
      
      Coordinate position = new Coordinate(5,3);
      Paper p = new Paper(12,10);
      Direction d = Direction.SOUTH_EAST;
      Turtle t = new Turtle(position, d, Pen.DOWN, p);
      t.changeBrush('#');
      t.move(10);
      
      /*
      
      t.changeBrush('#');
      t.move(2);
      t.rotate(Direction.NORTH_EAST, Rotation.RIGHT, 1);
      t.move(3);
      t.changeBrush('$');
      t.rotate(Direction.NORTH_EAST, Rotation.RIGHT, 3);
      t.move(3);
      t.changeBrush('#');
      t.rotate(Direction.NORTH_EAST, Rotation.LEFT, 2);
      t.move(6);
      t.rotate(Direction.NORTH_EAST, Rotation.RIGHT,3);
      t.move(3);
      t.rotate(Direction.NORTH_EAST, Rotation.RIGHT,1);
      t.move(4);
      
      */
      
      // t.move(0);
      //t.rotate(Direction.NORTH_EAST, Rotation.LEFT, 3);
      //t.move(3);
      //t.rotate(Direction.EAST, Rotation.RIGHT, 2);
      //t.move(3);
      
      t.turtleStats();
      System.out.println(p.toString());
      

      
      
      //Test cases
      //ENABLE ASSERTIONS
      //TestCases.Test.containsTest(p);
      
      
    }
}
