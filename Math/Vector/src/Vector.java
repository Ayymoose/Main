public class Vector {

  /*
   * Vector library for general use (Mainly 2D vector operations for now...) 
   * Created by Ayman Moussa @ 11:04 26/02/15
   * Can be used as Vector3D but Vector also includes Vector2D
   */
  
  private float x;
  private float y;
  
  //2-dimensional Vector constructor
  public Vector(float x,float y) {
    this.x = x;
    this.y = y;
  }
  
  //Default constructor
  public Vector() {
    x = 0.0f;
    y = 0.0f;
  }
  
 
  //Length of a 2-dimensional vector
  public float length2d() {
    return (float)Math.sqrt(x * x + y * y);
  }
  
  //Cross product of two 2-dimensional vectors
  public static float cross2d(Vector v1,Vector v2) {
    return (v1.x * v2.y) - (v1.y * v2.x);
  }
  
  //Compute the 2-dimensional dot product of v1 and v2
  public static float dot2d(Vector v1,Vector v2) {
    return v1.x * v2.x + v1.y * v2.y;
  }
  
  //Normalises a 2-dimensional vector
  public void normalize2d() {
    float length = length2d();
    x /= length;
    y /= length;
  }
  
  //Negates a 2-dimensional vector
  public void negate2d() {
    //So much easier in C++ with operator overloading
    x = -x;
    y = -y;
  }
  
  //Gets the vector from v1 to v2
  public Vector to2d(Vector v1,Vector v2) {
    //AB = B - A
    return new Vector(v2.x - v1.x,v2.y - v1.y);
  }
  
  //Adds an arbitrary amount of vectors together
  public static Vector add(Vector... vs) {
    
    float vx = 0.0f;
    float vy = 0.0f;
    
    for (Vector v : vs) {
      vx += v.x;
      vy += v.y;
    }
    return new Vector(vx,vy);
  }

  //Scalar multiplication by a scalar
  public void scalarMultiply2d(float scalar) {
    x *= scalar;
    y *= scalar;
  }
  
  //
  public String toString() {
    return "(" + x + "," + y + ")";
  }
  
}
