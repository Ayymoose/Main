package turtle;

public class Paper {
  
  private int width;
  private int height;
  private int[][] paper; //char?
  
  //Constructor
  public Paper(int width,int height) {
    this.width = width;
    this.height = height;
    paper = new int[height][width]; 
    //access is paper[y][x]
    //          paper[rows][cols]
    //          x -> height y->width
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
      paper[width - position.getY() - 1][position.getX()] = c;
    }
  }
  
  public void write(int x,int y,char c) { 
    if (contains(y,x)) {
      paper[y][x] = c;
    }
  }
  
  public String toString(Turtle t) {
    StringBuilder sb = new StringBuilder();
    for (int x=0; x<height; x++) {
      sb.append('[');
      for (int y=0; y<width; y++) {
        if (x == width - t.turtlePosition().getY() - 1 && y == t.turtlePosition().getX()) {
          sb.append('@');
        } else {
          sb.append(paper[x][y]);
        }
        if (y != width-1) {
          sb.append(',');
        }
      }
      sb.append(']');
      sb.append('\n');
    }

    return sb.toString();
  }
  

}
