package turtle;
//import java.lang.StringBuilder;

public class Paper {
  
  private int width;
  private int height;
  private int[][] paper; //char?
  
  //Constructor
  Paper(int width,int height) {
    this.width = width;
    this.height = height;
    paper = new int[width][height];
  }
  
  //Methods
  public int getWidth() {
    return width;
  }
  
  public int getHeight() {
    return height;
  }
  
  public boolean contains(int x,int y) {
    return (x >= 0 && y >=0 && y < height && x < width);
  }
  
  public boolean contains(Coordinate position) {
    return (position.getX() >= 0 && position.getY() >=0 && position.getX() < width && position.getY() < height);
  }
  
  public void write(Coordinate position,char c) {
    if (contains(position)) {
      paper[position.getX()][position.getY()] = c;
    }
  }
  
  public void write(int x,int y,char c) { 
    if (contains(x,y)) {
      paper[x][y] = c;
    }
  }
  
  public String toString(Turtle t) {
    StringBuilder sb = new StringBuilder();
    for (int x=0; x<width; x++) {
      sb.append('[');
      for (int y=0; y<height; y++) {
        if (x == t.turtlePosition().getX() && y == t.turtlePosition().getY()) {
          sb.append('@');
        } else {
          sb.append(paper[x][y]);
        }
        if (y != height-1) {
          sb.append(',');
        }
      }
      sb.append(']');
      sb.append('\n');
    }

    return sb.toString();
  }
  

}
