package turtle;

import java.io.FileNotFoundException;

import util.Direction;
import util.Pen;
import util.Rotation;


public class Main {

    public static void main(String[] args) throws FileNotFoundException {
      
    Paper p = new Paper(4,5);
    Turtle t = new Turtle(new Coordinate(2,2),Direction.NORTH,Pen.DOWN,p);
    t.changeBrush('#');
    
    
    //t.rotate(Direction.NORTH_EAST, Rotation.RIGHT, 1);
    //t.rotate(0,RIGHT,1);
    //t.rotate(45,RIGHT,1);
    
    /*
    t.move(1);
    System.out.println("Direction: " + t.turtleDirection());
    t.rotate(Direction.NORTH, Rotation.RIGHT,2);
    System.out.println("Direction: " + t.turtleDirection());
    t.move(2);
    */
   
    System.out.println(t.turtleDirection());
    
   // System.out.println(p.toString(t));
    
    /*
     * [1,1,1,1,1]
     * [1,1,1,1,1]
     * [1,1,1,1,1]
     * [1,1,1,1,1]
     * 
     */
      
      
    }
}
