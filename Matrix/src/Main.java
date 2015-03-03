import exception.MatrixDifferentDimensionsException;
import exception.NullMatrixException;

public class Main {

  public static void main(String[] args) {


    try {
      Matrix a = new Matrix(new double[][]
          {
            {1,2,3,4},
            {4,5,6,5},
            {7,8,9,6}
          }
          );

      Matrix b = new Matrix(new double[][]
          {
            {1,2,3},
            {4,5,6},
            {7,8,9},
            {1,2,4}
          }
          );


      Matrix c;
      try {

        c = Matrix.multiply(a, b);
        System.out.println(c);
      } catch (MatrixDifferentDimensionsException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }


    } catch (NullMatrixException e1) {
      // TODO Auto-generated catch block
      e1.printStackTrace();
    }





    /*
     *  3 x 4           4 x 3  
     * {1,2,3,4}       {1,2,3}   {x,x,x}
       {4,5,6,7}   X   {4,5,6} = {x,x,x}
       {7,8,9,0}       {7,8,9}   {x,x,x}
                       {1,2,4}   
     * 
     * 
     * 
     */





  }



}
