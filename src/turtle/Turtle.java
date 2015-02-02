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
  
  //' ' is the "empty" character here 
  //private char charRemaining = ' '; 
  
  //Because of the damn (0,0) in the bottom left corner 
  private final int yOffset;

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
  
  //Needed?
  public Coordinate turtlePosition() {
    return position;
  }
  
  public Direction turtleDirection() {
    return direction;
  }
  //
  
  public void turtleStats() {
    System.out.println("");
    System.out.println("Turtle is @" + position);
    System.out.println("Direction is " + direction);
    System.out.println("Pen is " + penState);
    System.out.println("Brush is " + (char)brush);
    System.out.println("");
  } 
  
  
  //
  
  //Change the state of the pen
  public void changePen(Pen penState) {
    this.penState = penState;
  }
  
  //Change the brush
  public void changeBrush(char brush) {
    this.brush = brush;
  }
  
  //Rotates the direction by rotation n times
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
      //Don't forget the remaining character
    //  charRemaining = brush;
      
      //Draw the character
      paper.write(position.getX(),yOffset  - position.getY(), brush);
    }
  }
  
  //Move steps steps in the current direction
  //CLEAN UP LATER
  public void move(int steps) {
    
    int turtleSteps,stepsMax;
    int currentX = position.getX();
    int currentY = position.getY();
    int dx,dy;
    
    //Erase the turtle
    paper.write(position.getX(), yOffset - position.getY(), '.');
    
    //Write the remaining character if there is one
    if (brush != ' ' && penState == Pen.DOWN) {
      paper.write(position.getX(), yOffset - position.getY(), brush);
    }
    
    switch (direction) {
      case NORTH:
        
        //Calculate the available steps remaining
        stepsMax = paper.getHeight() - currentY;
        //Always guaranteed to be within the paper dimensions
        turtleSteps = (steps < stepsMax ? currentY+steps : currentY+stepsMax-1);
        
        //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
        for (int i=currentY; i<turtleSteps; i++) {
          position.update(position.getX(),position.getY() + 1);
          draw();
        }
        
        break;
        
      case NORTH_EAST:
        
        //Available x and y left
        dx = paper.getWidth() - position.getX() - 1;
        dy = paper.getHeight() - position.getY() - 1;

        for (int i=0; i<steps && !(dx <= 0 || dy <=0); i++) {
          dx--; 
          dy--;
          position.update(position.getX() + 1,position.getY() + 1);
          draw();
        }
        
        break;
      case EAST:
        
        //Calculate the available steps remaining
        stepsMax = paper.getWidth() - currentX;
        //Always guaranteed to be within the paper dimensions
        turtleSteps = (steps < stepsMax ? currentX+steps : currentX+stepsMax-1);
        
        //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
        for (int i=currentX; i<turtleSteps; i++) {
          position.update(position.getX() + 1,position.getY());
          draw();
        }

        break;
      case SOUTH_EAST:
        
        //Available x and y left
        dx = paper.getWidth() - position.getX() - 1;
        dy = position.getY();

        System.out.println("dx: " + dx + "dy: " + dy);
        
        for (int i=0; i<steps && !(dx <= 0 || dy <=0); i++) {
          dx--;
          dy--;
          position.update(position.getX() + 1,position.getY() - 1);
          draw();
        }
        
        
        break;
      case SOUTH:
        
        //Calculate the available steps remaining
        stepsMax = currentY;
        //Always guaranteed to be within the paper dimensions
        turtleSteps = (steps < stepsMax ? steps : currentY);
        
        //System.out.println(turtleSteps);
        
        //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
        for (int i=0; i<turtleSteps; i++) {
          position.update(position.getX(),position.getY() - 1);
          draw();
        }
        
        
        break;
      case SOUTH_WEST:
        
        //Available x and y left
        dx = position.getX();
        dy = position.getY();
        
        for (int i=0; i<steps && !(dx <= 0 || dy <=0); i++) {
          dx--;
          dy--;
          position.update(position.getX() - 1,position.getY() - 1);
          draw();
        }
        
        break;
      case WEST:
        
        //Calculate the available steps remaining
        stepsMax = currentX;
        //Always guaranteed to be within the paper dimensions
        turtleSteps = (steps < stepsMax ? steps : currentX);
        
        //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
        for (int i=0; i<turtleSteps; i++) {
          position.update(position.getX() - 1,position.getY());
          draw();
        }
        
        break;
      default: //NORTH_WEST

        //Available x and y left
        dx = position.getX();
        dy = paper.getHeight() - position.getY() - 1;
        
        //System.out.println("dx : " + dx + " dy :" + dy);
        
        for (int i=0; i<steps && !(dx <= 0 || dy <=0); i++) {
          dx--;
          dy--;
          position.update(position.getX() - 1,position.getY() + 1);
          draw();
        }

        break;
    }
    //Draw and remember that there is a character at the turtle's position IF the pen is DOWN
    paper.write(position.getX(), yOffset - position.getY(), '@');
    
   
    
    
  }

}
