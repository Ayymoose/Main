package turtle;
import util.Direction;
import util.Pen;
import util.Rotation;

public class Turtle {
  
  private Coordinate position;
  private Direction direction;
  private Pen penState;
  private Paper paper;
  private char brush;
  
  //(0,0) is the bottom left corner of the paper
  private final int yOffset;
  private final char fillChar = ' ';

  //Constructor
  public Turtle(Coordinate position,Direction direction,Pen penState,Paper paper) {
    this.position = position;
    this.direction = direction;
    this.penState = penState;
    this.paper = paper;
    
    
    yOffset = paper.getHeight() - 1;
    
    //Update the paper with the turtle position
    //Because (0,0) is defined as the BOTTOM LEFT corner of the paper
    //This is the turtle's position in the paper
    //this.paper.write(position.getX(), yOffset - position.getY(), '@');
  }
  
  public Direction turtleDirection() {
    return direction;
  }
  
  //Change the state of the pen
  public void changePen(Pen penState) {
    this.penState = penState;
  }
  
  //Change the brush
  public void changeBrush(char brush) {
    this.brush = brush;
  }
  
  //Rotates the direction by rotation n times
  public void rotate(int angle,Rotation rotation,int n) {
    for (int i=0; i<n; i++) {
     direction = direction.rotate(rotation);
    }
  }
  
  //Draws if the pen is DOWN with the current brush
  public void draw() {
    if (penState == Pen.DOWN) {
      //Draw the character
      paper.write(position.getX(),yOffset  - position.getY(), brush);
      //System.out.println(position);
    }
  }
  
  //Move steps steps in the current direction
  //TODO: Finish
  public void move(int steps) {
  
    int stepX = 0;
    int stepY = 0;

    //Erase the turtle
    //paper.write(position.getX(), yOffset - position.getY(), fillChar);
    
    //Write the remaining character if there is one
    /*if (brush != ' ' && penState == Pen.DOWN) {
      paper.write(position.getX(), yOffset - position.getY(), brush);
    }*/
    
    switch (direction) {
      case NORTH:
        stepY = 1;
        break;
      case EAST:
        stepX = 1;
        break;
      case SOUTH:
        stepY = -1;
        break;
      case WEST:
        stepX = -1;
        break;
      case NORTH_EAST:
        stepX = 1;
        stepY = 1;
        break;
      case NORTH_WEST:
        stepX = 1;
        stepY = -1;
        break;
      case SOUTH_EAST:
        stepX = -1;
        stepY = -1;
        break;
      default: // SOUTH_WEST
        stepX = -1;
        stepY = 1;
        break;
    }
      

    //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
    for (int i=0; i<steps; i++) {
      if (paper.contains(position.getX() + stepX,position.getY() + stepY)) {
        position.update(position.getX() + stepX,position.getY() + stepY);
      }
      draw();
    }
    
    
  }
  
    
    //Draw and remember that there is a character at the turtle's position IF the pen is DOWN
    //paper.write(position.getX(), yOffset - position.getY(), '@');
  

}
  
  
  
  
