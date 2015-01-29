package turtle;

public class Coordinate {
  private int x;
  private int y;
  
  //In an array
  //x = ROW
  //y = COL
  
  
  
  public Coordinate(int x,int y) {
    this.x = x;
    this.y = y;
  }
  
  public int getX() {
    return x;
  }
  
  public int getY() {
    return y;
  }
  
  public void update(int x,int y) {
    this.x = x;
    this.y = y;
  }
  
  public String toString() {
    return "(" + x + "," + y + ")";
  }
  
}