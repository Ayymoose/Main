import exception.MatrixDifferentDimensionsException;
import exception.MatrixIndexOutOfBoundsException;
import exception.NullMatrixException;

public class Matrix {

  private int rows;
  private int cols;
  private double[][] matrix;
  
  //Constructor that initialises an empty matrix
  public Matrix(int rows,int cols) throws NullMatrixException {
    //Populate the array with the data
    if (rows == 0 || cols == 0) {
      throw new NullMatrixException();
    }
    this.rows = rows;
    this.cols = cols;
    matrix = new double[rows][cols];
  }
  
  //Constructor that initialises a matrix with data
  public Matrix(double[][] data) throws NullMatrixException {
    //Populate the array with the data
    rows = data.length;
    cols = data[0].length;
    
    if (rows == 0 || cols == 0) {
      throw new NullMatrixException();
    }
    
    matrix = new double[rows][cols];
    
    for (int row=0; row<getRows(); row++) {
      for (int col=0; col<getColumns(); col++) {
        matrix[row][col] = data[row][col];
      }
    }
  }
  
  //Returns the value stored in the matrix at [row][col]
  public double at(int row,int col) throws MatrixIndexOutOfBoundsException {
    if (row < 0 || col < 0 || row >= rows || col >= cols) {
      throw new MatrixIndexOutOfBoundsException();
    }
    return matrix[row][col];
  }
  
  //Stores data at [row][col]
  public void store(int row,int col,double data) throws MatrixIndexOutOfBoundsException {
    if (row < 0 || col < 0 || row >= rows || col >= cols) {
      throw new MatrixIndexOutOfBoundsException();
    }
    matrix[row][col] = data;
  }
  
  //Multiplies two matrices and returns a third matrix
  public static Matrix multiply(Matrix m1,Matrix m2) throws MatrixDifferentDimensionsException, NullMatrixException {
    //Pre : m1.getCols() = m2.getRows()
    //Post : Returns the matrix that is the result from the multiplication of m1 and m2
    //Throws: MatrixDifferentDimensions exception if Pre is violated
    
    //Optimise with loop interchange and direct manipulation (avoid function calls)
    //Doubles are somewhat expensive
    
    if (m1 == null || m2 == null) {
      throw new NullMatrixException();
    }
    
    //Cache results
    int rowM1 = m1.getRows();
    int colM1 = m1.getColumns();
    
    //Violates pre (Comment out block exception blocks out for optimisation speed tests)
    if (colM1 != m2.getRows()) {
      throw new MatrixDifferentDimensionsException();
    }
    //
    
    int colM2 = m2.getColumns();
    
    //Result matrix
    Matrix m3 = new Matrix(rowM1,colM2);
    
    int rowM3 = m3.getRows();
    int colM3 = m3.getColumns();
    
    //O(n^3) complexity
    for (int row=0; row<rowM3; row++) {
      for (int col=0; col<colM3; col++) {
        int sum = 0;
        for (int k=0; k<colM1; k++) {
          sum += m1.matrix[row][k] * m2.matrix[k][col];
        }
        m3.matrix[row][col] = sum;
      }
    }
    return m3;
  }
  
  //Multiplies each element in the matrix by scalar
  public void multiplyScalar(int scalar) {
    for (int row=0; row<rows; row++) {
      for (int col=0; col<cols; col++) {
        matrix[row][col] *= scalar;
      }
    }
  }
  
  //Interchanges the rows and columns of the matrix
  //TODO: Implement
  public static Matrix transpose() {
    return null;
  }
  
  //Returns true if the matrix is a square matrix
  public boolean isSquare() {
    return (rows == cols);
  }
  
  //Returns the inverse of a matrix (if it has one)
  //TODO: Implement
  public Matrix inverse() {  
    return null;
  }
  
  //Returns the determinant of a matrix (if it exists)
  //TODO: Implement
  public double determinant() {
   return 0.0; 
  }
  
  //Number of rows
  public int getRows() {
    return rows;
  }
  
  //Number of columns
  public int getColumns() {
    return cols;
  }

  //String representation
  public String toString() {
    StringBuilder sb = new StringBuilder();
    for (int row=0; row<getRows(); row++) {
      sb.append('{');
      for (int col=0; col<getColumns(); col++) {
        sb.append(matrix[row][col]);
        sb.append((col==getColumns()-1 ? "" : ','));
      }
      sb.append('}');
      sb.append('\n');
    }
    return sb.toString();
  }
  
}
