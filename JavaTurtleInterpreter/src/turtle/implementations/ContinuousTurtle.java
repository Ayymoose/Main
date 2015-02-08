package turtle.implementations;

import turtle.Coordinate;
import turtle.Paper;

public class ContinuousTurtle extends AbstractTurtle {
   
  public ContinuousTurtle (Paper paper,Coordinate coordinate) {
    super(paper,coordinate);
  }
  
  @Override
  //TODO: Unsure if this is correct 
  public void move(int steps) {
    //This turtle just wonders off the paper , no need to draw just track its position
    int stepX = direction.getStepX();
    int stepY = direction.getStepY();
    
    for (int i=0; i<steps; i++) {
      //if (paper.contains(coordinate.getX() + stepX,coordinate.getY() + stepY)) {
        
      //}
      coordinate.update(coordinate.getX() + stepX,coordinate.getY() + stepY);
      draw();
    }
    
  }


}
