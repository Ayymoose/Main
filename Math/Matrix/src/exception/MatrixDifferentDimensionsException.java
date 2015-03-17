package exception;

public class MatrixDifferentDimensionsException extends Exception {
  
  public MatrixDifferentDimensionsException() {
    super("Matrices are of different dimensions.");
  }

}
