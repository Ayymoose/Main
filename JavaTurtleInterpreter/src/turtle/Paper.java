package turtle;

public class Paper {
  
  private int rows;
  private int cols;
  private char[][] paper;
  private final char fillChar = '.';
  
  //Constructor
  public Paper(int width,int height) {
    cols = width;
    rows = height;
    paper = new char[rows][cols]; 
            // paper[rows][cols]
            // paper[height][width]
            // paper[y][x]
    
    //Initialise with blank spaces
    for (int x=0; x<rows; x++) {
      for (int y=0; y<cols; y++) {
        paper[x][y] = fillChar;
      }
    }
  }
  
  //Return width of paper
  public int getWidth() {
    return cols;
  }
  
  //Return height of paper
  public int getHeight() {
    return rows;
  }
  
  //Return whether a given x and y is contained within the paper
  public boolean contains(int x,int y) {
    return (x >= 0 && y >=0 && y < rows && x < cols);
  }
  
  public boolean contains(Coordinate position) {
    return (position.getX() >= 0 && position.getY() >=0 && position.getY() < rows && position.getX() < cols);
  }
  
  public void write(Coordinate position,char character) {
    if (contains(position)) {
      paper[position.getY()][position.getX()] = character;
    }
  }
  
  public void write(int x,int y,char c) { 
    if (contains(x,y)) {
      paper[y][x] = c;
    }
  }
  
  public String toString() {
    StringBuilder sb = new StringBuilder();
    for (int x=0; x<rows; x++) {
      for (int y=0; y<cols; y++) {
        sb.append(paper[x][y]);
      }
      sb.append('\n');
    }
    return sb.toString();
  }
}
