package queue;

public class Node<T> {
  
  private T element;
  private Node<T> next;
  
  public void setElement(T element) {
    this.element = element;
  }
  
  public T getElement() {
    return element;
  }
  
  public void setNext(Node<T> newNode) {
    next = newNode;
  }
  
  public Node<T> getNext() {
    return next;
  }
  
}
