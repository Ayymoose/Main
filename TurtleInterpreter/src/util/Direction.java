package util;

public enum Direction {
  NORTH(360),//360
  NORTH_EAST(45),//45
  EAST(90),//90
  SOUTH_EAST(135),//135
  SOUTH(180),//180
  SOUTH_WEST(225),//225
  WEST(270),//270
  NORTH_WEST(305);//305

  //This code makes me cringe
  
  
  private int angle;
  
  Direction(int angle) {
    this.angle = angle;
  }
  
  //Overload without duplicating the code?
  public static Direction getDirectionFromAngle(int angle) {
    switch (angle) {
      case 360:
        return NORTH;
      case 45:
        return NORTH_EAST;
      case 90:
        return EAST;
      case 135:
        return SOUTH_EAST;
      case 180:
        return SOUTH;
      case 225:
        return SOUTH_WEST;
      case 270:
        return WEST;
      default:
        return NORTH_WEST;
  }
}
  
  public Direction getDirection() {
    switch (angle) {
      case 360:
        return NORTH;
      case 45:
        return NORTH_EAST;
      case 90:
        return EAST;
      case 135:
        return SOUTH_EAST;
      case 180:
        return SOUTH;
      case 225:
        return SOUTH_WEST;
      case 270:
        return WEST;
      default:
        return NORTH_WEST;
  }
}
  
  //Returns the direction after applying rotation once
  public Direction rotate(Rotation rotation) {
    switch (rotation) {
      case LEFT:
        switch (angle) {
          case 360:
            angle = 305;
            return NORTH_WEST;
          case 45:
            angle = 360;
            return NORTH;
          case 90:
            angle = 45;
            return NORTH_EAST;
          case 135:
            angle = 90;
            return EAST;
          case 180:
            angle = 135;
            return SOUTH_EAST;
          case 225:
            angle = 180;
            return SOUTH;
          case 270:
            angle = 225;
            return SOUTH_WEST;
          default:
            angle = 270;
            return WEST;
        }
      default:
        switch (angle) {
          case 360:
            angle = 45;
            return NORTH_EAST;
          case 45:
            angle = 90;
            return EAST;
          case 90:
            angle = 135;
            return SOUTH_EAST;
          case 135:
            angle = 180;
            return SOUTH;
          case 180:
            angle = 225;
            return SOUTH_WEST;
          case 225:
            angle = 270;
            return WEST;
          case 270:
            angle = 305;
            return NORTH_WEST;
          default:
            angle = 360;
            return NORTH;
        }
    }
  }

}


/*
 * 
 * Direction d = new Direction(Direction.NORTH_EAST) (45)
 * d.rotate(Rotation.RIGHT) == EAST
 * 
 */
