package turtle.implementations;

import turtle.Coordinate;
import turtle.Turtle;
import turtle.Paper;
import util.Direction;
import util.Pen;
import util.Rotation;

public abstract class AbstractTurtle implements Turtle {
  
  Pen penState = Pen.UP;
  Direction direction = Direction.NORTH;
  Paper paper;
  Coordinate coordinate;
  char brush = '*';
  int yOffset;
  
  public AbstractTurtle(Paper paper,Coordinate coordinate) {
    this.coordinate = coordinate;
    this.paper = paper;
    yOffset = paper.getHeight() - 1;
  }
  
  public AbstractTurtle(AbstractTurtle[] turtles) {
    // TODO Auto-generated constructor stub
    System.out.println("System processing");
  }

  @Override
  public void changeBrush(char brush) {
    this.brush = brush;
  }
  
  @Override
  public void changePen(Pen penState) {
    this.penState = penState;
  }
  
  @Override
  public void draw() {
    if (penState == Pen.DOWN && paper.contains(coordinate.getX(),yOffset  - coordinate.getY())) {
      paper.write(coordinate.getX(),yOffset  - coordinate.getY(), brush);
    }
  }
  
  @Override
  public void move(int steps) {
    
    int stepX = direction.getStepX();
    int stepY = direction.getStepY();
    //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
    for (int i=0; i<steps; i++) {
      if (paper.contains(coordinate.getX() + stepX,coordinate.getY() + stepY)) {
        coordinate.update(coordinate.getX() + stepX,coordinate.getY() + stepY);
      }
      draw();
    }
  }
  
  @Override
  public void rotate(int angle,Rotation rotation,int n) {
    for (int i=0; i<n; i++) {
      direction = direction.rotate(rotation);
    }
  }
  
}
