package turtle;

import util.Pen;
import util.Rotation;

public interface Turtle {

  
  void changePen(Pen penState);
  
  void changeBrush(char brush);
  
  void draw();
  
  void move(int steps);
  
  void rotate(int angle,Rotation rotation,int n);
	
}
