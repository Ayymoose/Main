package turtle.implementations;

import turtle.Coordinate;
import turtle.Paper;

public class BouncyTurtle extends AbstractTurtle {
   
  public BouncyTurtle (Paper paper,Coordinate coordinate) {
    super(paper,coordinate);
  }
  
  @Override
//TODO: Unsure if this is correct 
  public void move(int steps) {
    
    //This turtle just reverses the direction once it hits the edge
    
    int stepX = direction.getStepX();
    int stepY = direction.getStepY();
    
    for (int i=0; i<steps; i++) {
      if (paper.contains(coordinate.getX() + stepX,coordinate.getY() + stepY)) {
        coordinate.update(coordinate.getX() + stepX,coordinate.getY() + stepY);
      } else {
        stepX *= -1;
        stepY *= -1;
      }
      draw();
    }
    
    
  }


}
