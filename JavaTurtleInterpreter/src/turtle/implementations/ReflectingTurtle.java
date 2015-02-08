package turtle.implementations;

import turtle.Coordinate;
import turtle.Paper;
import util.Direction;
import util.Rotation;

public class ReflectingTurtle extends AbstractTurtle {
   
  public ReflectingTurtle (Paper paper,Coordinate coordinate) {
    super(paper,coordinate);
  }
  
  @Override
  public void move(int steps) {
    
    //This turtle 'bounces' inside the paper at 45 degree angles
    
    int stepX = direction.getStepX();
    int stepY = direction.getStepY();
    
    for (int i=0; i<steps; i++) {
      if (paper.contains(coordinate.getX() + stepX,coordinate.getY() + stepY)) {
        coordinate.update(coordinate.getX() + stepX,coordinate.getY() + stepY);
      } else {
        
        //System.out.println(direction);

        
        switch (direction) {
        case NORTH_EAST:
        case SOUTH_EAST:
        case SOUTH_WEST:
        case NORTH_WEST:
          switch (direction) {
          case NORTH_EAST:
            direction = (coordinate.getY() >= paper.getHeight()-1 ? Direction.SOUTH_EAST : Direction.NORTH_WEST);
            break;
          case SOUTH_EAST:
            direction = (coordinate.getY() <= 0 ? Direction.NORTH_EAST : Direction.SOUTH_WEST);
            break;
          case SOUTH_WEST:
            direction = (coordinate.getX() <= 0 ? Direction.SOUTH_EAST : Direction.NORTH_WEST);
            break;
          case NORTH_WEST:
            direction = (coordinate.getX() <= 0 ? Direction.NORTH_EAST : Direction.SOUTH_WEST);
            break;
          }
          stepX = direction.getStepX();
          stepY = direction.getStepY();
          break;
        case NORTH:
          stepY = -1;
          direction = Direction.SOUTH;
          break;
        case EAST:
          stepX = -1;
          direction = Direction.WEST;
          break;
        case SOUTH:
          stepY = 1;
          direction = Direction.NORTH;
          break;
        case WEST:
          stepX = 1;
          direction = Direction.EAST;
          break;
        }
      }
      draw();
    }
    
    
  }


}
