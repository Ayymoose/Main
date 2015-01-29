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
      paper[position.getY() ][width - position.getX() - 1] = c;
    }
  }
  
  public void write(int x,int y,char c) { 
    if (contains(y,x)) {
      paper[y][x] = c;
    }
  }
  
  public String toString(Turtle t) {
    StringBuilder sb = new StringBuilder();
    for (int x=height-1; x!=-1; x--) {
      sb.append('[');
      for (int y=width-1; y!=-1; y--) {
        if (x == t.turtlePosition().getY()  && y == width - t.turtlePosition().getX() - 1 ) { //Turtle pos
          sb.append('@');
        } else {
          sb.append(paper[x][y]);
        }
        if (y != 0) {
          sb.append(',');
        }
      }
      sb.append(']');
      sb.append('\n');
    }

    return sb.toString();
  }
  

}
