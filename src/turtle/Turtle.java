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
  public Turtle(Coordinate position,Direction direction,Pen penState,Paper paper) {
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
  
  public void turtleStats() {
    System.out.println("");
    System.out.println("\\**********************/");
    System.out.println("Turtle is @" + position);
    System.out.println("Direction is " + direction);
    System.out.println("Pen is " + penState);
    System.out.println("Brush is " + (int)brush);
    System.out.println("\\**********************/");
    System.out.println("");
    
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
    //Started and finished @ 13:29! (the day after that!) 
    for (int i=0; i<n; i++) {
      this.direction = direction.rotate(rotation);
    }
  }
  
  public void draw() {
    if (penState == Pen.DOWN) {
      paper.write(position, brush);
    }
  }
  
  public void move(int steps) {
    

    
    int turtleSteps;
    int stepsMax;
    int currentX;
    int currentY;
    
    switch (direction) {
      case NORTH:
        
        currentY = position.getY();
        
        //Calculate the available steps remaining
        stepsMax = paper.getHeight() - currentY;
        
        turtleSteps = (steps < stepsMax ? currentY+steps : currentY+stepsMax-1);
        
        for (int i=currentY; i<turtleSteps; i++) {
          draw();
          //paper.write(position,brush);
          position.update(position.getX(),position.getY()+1);
        }

        break;
        
      case NORTH_EAST:
        
        
        
        break;
      case EAST:
        
        currentX = position.getX();
        
        //Calculate the available steps remaining
        stepsMax = paper.getWidth() - currentX;
        turtleSteps = (steps < stepsMax ? currentX+steps : currentX+stepsMax-1);
        
        for (int i=currentX; i<turtleSteps; i++) {
          draw();
          //paper.write(position,brush);
          position.update(position.getX()+1,position.getY());
        }
        
        
        break;
      case SOUTH_EAST:
        break;
      case SOUTH:
        
        currentY = position.getY();

        //Calculate the available steps remaining
        stepsMax = paper.getHeight() - currentY;
        turtleSteps = (steps < stepsMax ? currentY+steps : currentY+stepsMax-1);

        for (int i=currentY; i<turtleSteps; i++) {
          draw();
          //paper.write(position,brush);
          position.update(position.getX(),position.getY()-1);
        }


        
        break;
      case SOUTH_WEST:
        break;
      case WEST:
        
        
        currentX = position.getX();

        //Calculate the available steps remaining
        stepsMax = paper.getWidth() - currentX;
        turtleSteps = (steps < stepsMax ? currentX+steps : currentX+stepsMax-1);

        for (int i=currentX; i<turtleSteps; i++) {
          draw();
          //paper.write(position,brush);
          position.update(position.getX()-1,position.getY());
        }

        
        
        break;
      default:


        currentY = position.getY();
        currentX = position.getX();
        
       
        
        int dx = position.getX();
        int dy = paper.getHeight() - currentY - 1;
        
        stepsMax = Math.min(dx,dy);
        
        //System.out.println("Avail X " + dx);
        //System.out.println("Avail Y " + dy);
        System.out.println("StepMax " + stepsMax);
        
        turtleSteps = (steps < stepsMax ? currentX+steps : currentX+stepsMax);

        for (int i=currentX; i<turtleSteps; i++) {
          draw();
          //paper.write(position.getX(), position.getY(),brush);
          position.update(position.getX()-1,position.getY()+1);
        }
        
        
        
        
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
