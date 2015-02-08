package turtle.implementations;

import turtle.Coordinate;
import turtle.Paper;

public class WrappingTurtle extends AbstractTurtle {
   
  public WrappingTurtle (Paper paper,Coordinate coordinate) {
    super(paper,coordinate);
  }
  
  @Override
  public void move(int steps) {

    int stepX = direction.getStepX();
    int stepY = direction.getStepY();

    //Move and then draw and when the turtle stops with the pen DOWN there is a character underneath
    for (int i=0; i<steps; i++) {
      if (paper.contains(coordinate.getX() + stepX,coordinate.getY() + stepY)) {
        coordinate.update(coordinate.getX() + stepX,coordinate.getY() + stepY);
      } else {
        
        switch (direction) {
        case NORTH:
          coordinate.update(coordinate.getX(), 0);
          break;
        case NORTH_EAST:
          if (coordinate.getX() >= paper.getWidth()-1) {
            coordinate.update(paper.getWidth() - coordinate.getY() - 1, 0);
          } else if (coordinate.getY() >= paper.getHeight()-1) {
            coordinate.update(0, paper.getHeight() - coordinate.getX() - 1);
          }
        break;
        case EAST:
          coordinate.update(0, coordinate.getY());
          break;
        case SOUTH_EAST:
          if (coordinate.getX() >= paper.getWidth()-1) {
            coordinate.update(paper.getWidth() - (paper.getHeight() - coordinate.getY()),paper.getHeight()-1);
          } else if (coordinate.getY() <= 0) {
            coordinate.update(0, coordinate.getX());
          }
          break;
        case SOUTH:
          coordinate.update(coordinate.getX(), paper.getHeight()-1);
          break;
          
        case SOUTH_WEST:
          if (coordinate.getX() <= 0) {
            coordinate.update(paper.getWidth() - coordinate.getY() - 1,paper.getHeight()-1);
          } else if (coordinate.getY() <= 0) {
            coordinate.update(paper.getWidth()-1, paper.getHeight() - coordinate.getX() - 1);
          }
          break;
        case WEST:
          coordinate.update(paper.getWidth()-1, coordinate.getY());
          break;
        case NORTH_WEST:
          if (coordinate.getX() <= 0) {
            coordinate.update(coordinate.getY(), 0);
          } else if (coordinate.getY() >= paper.getHeight()-1) {
            coordinate.update(paper.getWidth()-1, paper.getHeight() - (paper.getWidth() -coordinate.getX()));
          }
          break;
        }

      }
      draw();
    }


  }
  
  
  
  /*
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   * . . . . . . . . . . . .
   */

}
