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
  private final char fillChar = '.';

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
    this.paper.write(position.getX(), yOffset - position.getY(), '@');
  }
  
  public Direction turtleDirection() {
    return direction;
  }
  
  //Debugging
  public void turtleStats() {
    System.out.println("");
    System.out.println("Turtle is @" + position);
    System.out.println("Direction is " + direction);
    System.out.println("Pen is " + penState);
    System.out.println("Brush is " + (char)brush);
    System.out.println("");
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
  //Not working
  public void rotate(Direction direction,Rotation rotation,int n) {
    //Left off @17:53
    //Left off @17:54 (the next day)
    //Started and finished @ 13:29! (the day after that!) 
    for (int i=0; i<n; i++) {
      this.direction = direction.rotate(rotation);
    }
  }
  
  //Draws if the pen is DOWN with the current brush
  public void draw() {
    if (penState == Pen.DOWN) {
      //Draw the character
      paper.write(position.getX(),yOffset  - position.getY(), brush);
    }
  }
  
  //Move steps steps in the current direction
  public void move(int steps) {
    
    int turtleSteps,stepsMax=0;
    int currentX = position.getX();
    int currentY = position.getY();
    int dx=0,dy=0;
    int stepX = 0,stepY = 0;
    boolean canMove = true;
    boolean diagonal = false;
    
    //Erase the turtle
    paper.write(position.getX(), yOffset - position.getY(), fillChar);
    
    //Write the remaining character if there is one
    if (brush != ' ' && penState == Pen.DOWN) {
      paper.write(position.getX(), yOffset - position.getY(), brush);
    }
    
    switch (direction) {
      case NORTH:
      case EAST:
      case SOUTH:
      case WEST:
      case NORTH_EAST:
      case NORTH_WEST:
      case SOUTH_EAST:
      case SOUTH_WEST:
      
        switch (direction) {
          case NORTH:
            stepX = 1;
            stepsMax = paper.getHeight() - currentY;
            break;
          case EAST:
            stepX = 1;
            stepsMax = paper.getWidth() - currentX;
            break;
          case SOUTH:
            stepY = -1;
            stepsMax = currentY+1;
            break;
          case WEST:
            stepX = -1;
            stepsMax = currentX+1;
            break;
          case NORTH_EAST:
            dx = paper.getWidth() - position.getX() - 1;
            dy = paper.getHeight() - position.getY() - 1;
            stepsMax = Math.min(dx, dy);
            stepX = 1;
            stepY = 1;
            diagonal = true;
            break;
          case SOUTH_EAST:
            stepX = 1;
            stepY = -1;
            dx = paper.getWidth() - position.getX() - 1;
            dy = position.getY();
            stepsMax = Math.min(dx, dy);
            diagonal = true;
            break;
          case SOUTH_WEST:
            stepX = -1;
            stepY = -1;
            dx = position.getX();
            dy = position.getY();
            stepsMax = Math.min(dx, dy);
            diagonal = true;
            break;
          default: //NORTH_WEST
            stepX = -1;
            stepY = 1;
            dx = position.getX();
            dy = paper.getHeight() - position.getY() - 1;
            stepsMax = Math.min(dx, dy);
            diagonal = true;
            break;
        }
        
        //Always guaranteed to be within the paper dimensions
        turtleSteps = (steps < stepsMax ? steps : stepsMax-1);
        //System.out.println(turtleSteps);
        
        if (diagonal) {
          canMove = (!(dx <= 0 || dy <=0));
          turtleSteps++;
        }
        
        //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
        for (int i=0; i<turtleSteps && canMove; i++) {
          position.update(position.getX() + stepX,position.getY() + stepY);
          draw();
          if (diagonal) {
            canMove = (!(dx <= 0 || dy <=0));
            dx--;
            dy--;
          }
        }
        break;
    }
    //Draw and remember that there is a character at the turtle's position IF the pen is DOWN
    paper.write(position.getX(), yOffset - position.getY(), '@');
  }

}
