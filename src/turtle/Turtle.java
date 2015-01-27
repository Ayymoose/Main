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
  

  //Constructor
  Turtle(Coordinate position,Direction direction,Pen penState,Paper paper) {
    this.position = position;
    this.direction = direction;
    this.penState = penState;
    this.paper = paper;
  }
  
  //
  public Coordinate turtlePosition() {
    return position;
  }
  
  public Direction turtleDirection() {
    return direction;
  }
  
  
  //
  
  public void changePen(Pen penState) {
    this.penState = penState;
  }
  
  public void changeBrush(char brush) {
    this.brush = brush;
  }
  
  public void rotate(Direction direction,Rotation rotation,int n) {
    //Left off @17:53
    //Left off @17:54 (the next day)

    
  }
  
  public void draw() {
    if (penState == Pen.DOWN) {
      paper.write(position, brush);
    }
  }
  
  public void move(int steps) {
    
    int stepsAvailable;
    int currentX;
    int currentY;
    
    switch (direction) {
      case NORTH:
        currentX = position.getX();
        
        for (int i=currentX; i<currentX+steps; i++) {
          paper.write(position.getX(), position.getY(),brush);
          position.update(position.getX()-1,position.getY());
        }
        break;
        
      case NORTH_EAST:
        
        
        
        break;
      case EAST:
        
        currentY = position.getY();
        for (int i=currentY; i<currentY+steps; i++) {
          paper.write(position.getX(), position.getY(),brush);
          position.update(position.getX(),position.getY()+1);
        }
        
        
        break;
      case SOUTH_EAST:
        break;
      case SOUTH:
        
        break;
      case SOUTH_WEST:
        break;
      case WEST:
        break;
      default:

        break;
    }
  }
  
  /*
   * 
   * [0,0,0,0,0]
   * [0,0,0,0,0]
   * [0,x,0,0,0]
   * [0,0,0,0,0]
   */
   

  
}
