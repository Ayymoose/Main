package util;

public enum Direction {
  NORTH(0,0,1),
  NORTH_EAST(45,1,1),
  EAST(90,1,0),
  SOUTH_EAST(135,1,-1),
  SOUTH(180,0,-1),
  SOUTH_WEST(225,-1,-1),
  WEST(270,-1,0),
  NORTH_WEST(315,-1,1);

  private int angle;
  private int stepX;
  private int stepY;
  private final int rotateBy = 45;
  
  Direction(int angle,int stepX,int stepY) {
    this.angle = angle;
    this.stepX = stepX;
    this.stepY = stepY;
  }
  
  public int getStepX() {
    return stepX;
  }
  
  public int getStepY() {
    return stepY;
  }
  
  //Returns the direction after applying rotation once
  public Direction rotate(Rotation rotation) {
    
    int newAngle = angle + (rotateBy * (rotation == Rotation.LEFT ? -1 : 1));
    newAngle = (newAngle < 0 ? 360 + newAngle : newAngle) % 360;
    
    switch (newAngle) {
    case 0:
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
    case 315:
      return NORTH_WEST;
    default: 
      return NORTH;
    }
    
  }

}
