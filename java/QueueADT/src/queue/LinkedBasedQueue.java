package queue;
import java.util.Iterator;

import exception.QueueException;


public class LinkedBasedQueue<T> implements Queue<T> {
  
  private Node<T> first;
  private Node<T> last;
  
  public LinkedBasedQueue() {
    first = last = null;
  }

  @Override
  public boolean isEmpty() {
    return (first == null) || (last == null);
  }

  @Override
  public void enqueue(T element) throws QueueException {
    Node<T> newNode = new Node<T>();
    newNode.setElement(element);
    if (isEmpty()) {
      first = last = newNode;
    } else {
      last.setNext(newNode);
      last = newNode;
    }
  }

  @Override
  public T getFront() throws QueueException {
    if (!isEmpty()) {
      return first.getElement();  
    } else {
      throw new QueueException("getFront on empty queue.");
    }
  }

  @Override
  public T dequeue() throws QueueException {
    if (!isEmpty()) {
      if (first == last) {
        last = null;
      }
      T result = first.getElement();
      first = first.getNext();
      return result;
    } else {
      throw new QueueException("Dequeue on empty queue");
    }
  }

  @Override
  public Iterator<T> iterator() {
    return new Iterator<T>() {
      @Override
      public boolean hasNext() {
        if (isEmpty()) {
          return false;
        } else {
          return first != null;
        }
      }

      @Override
      public T next() {
        T result = first.getElement();
        first = first.getNext();
        return result;
      }

      @Override
      public void remove() {
        //Undefined
      }
    };
  }

}
