
public class Main {
  
  
  public static void main(String[] args) {
    
    Vector v1 = new Vector(2.0f,5.0f);
    Vector v2 = new Vector(-6.0f,3.0f);
    Vector v3 = new Vector(1.0f,8.0f);
    
    Vector v4 = new Vector(3.0f,4.0f);
    v4 = Vector.add(v1,v2,v3);
    v4.scalarMultiply2d(2.0f);
    
    v4.normalize2d();
    
    System.out.println(v4.length2d());
    
    
  }

}
