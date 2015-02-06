package util;

public enum Direction {
  NORTH(0),
  NORTH_EAST(45),
  EAST(90),
  SOUTH_EAST(135),
  SOUTH(180),
  SOUTH_WEST(225),
  WEST(270),
  NORTH_WEST(315);

  private int angle;
  private final int rotationAngle = 45;
  
  Direction(int angle) {
    //System.out.println("Constructor with " + angle);
    this.angle = angle;
  }
  
  //Returns the direction after applying rotation once
  public Direction rotate(Rotation rotation,int angleRotation) {
    

    
    System.out.println("angle is " + angle);
    angle += (angleRotation * (rotation == Rotation.LEFT ? -1 : 1));
    System.out.println("angle is " + angle + " after rotating " + rotation + " by " + angle);
    angle = (angle < 0 ? 360 + angle : angle) % 360;
    System.out.println("angle is " + angle + " final");
  
    //Fucking bug in this code 
    //Wasted 2 hours+
    //@1:42 AM Debugging
    
    switch (angle) {
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