package util;

public enum Direction {
  
  NORTH(0),
  NORTH_EAST(45),
  EAST(90),
  SOUTH_EAST(135),
  SOUTH(180),
  SOUTH_WEST(225),
  WEST(270),
  NORTH_WEST(305);
  
  private int angle;
  
  Direction(int angle) {
    this.angle = angle;
  }
  
  //Returns the direction after applying rotation once
  public Direction rotate(Direction direction,Rotation rotation) {
    switch (rotation) {
      case LEFT:
        switch (direction) {
          case NORTH:
            return NORTH_WEST;
          case NORTH_EAST:
            return NORTH;
          case EAST:
            return NORTH_EAST;
          case SOUTH_EAST:
            return EAST;
          case SOUTH:
            return SOUTH_EAST;
          case SOUTH_WEST:
            return SOUTH;
          case WEST:
            return SOUTH_WEST;
          default:
            return WEST;
        }
      default:
        switch (direction) {
          case NORTH:
            return NORTH_EAST;
          case NORTH_EAST:
            return EAST;
          case EAST:
            return SOUTH_EAST;
          case SOUTH_EAST:
            return SOUTH;
          case SOUTH:
            return SOUTH_WEST;
          case SOUTH_WEST:
            return WEST;
          case WEST:
            return NORTH_WEST;
          default:
            return NORTH;
        }
    }
  }

}

