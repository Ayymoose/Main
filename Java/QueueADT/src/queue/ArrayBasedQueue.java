package queue;
import java.util.Iterator;

import exception.QueueException;


public class ArrayBasedQueue<T> implements Queue<T> {

  //Implemented using a circular queue
  
  private static final int maxQueue = 50;
  private T[] queue;
  private int first,last,count;
  
  
  public ArrayBasedQueue() {
    queue = (T[]) new Object[maxQueue];
    first = count = 0;
    last = maxQueue - 1;
  }
  
  public boolean isFull() {
    return count == maxQueue;
  }
  
  @Override
  public boolean isEmpty() {
    return count == 0;
  }

  @Override
  public void enqueue(T element) throws QueueException {
    if (!isFull()) {
      queue[last = (last + 1) % maxQueue] = element;
      count++;  
    } else {
      throw new QueueException("QueueOverflow on enqueue.");
    }
  }

  @Override
  public T getFront() throws QueueException {
    return queue[first];
  }

  @Override
  public T dequeue() throws QueueException {
    if (!isEmpty()) {
      T queueFront = queue[first];
      first = (first + 1) % maxQueue;
      count--;
      return queueFront;
    } else {
      throw new QueueException("Queue is empty on dequeue.");
    }
  }

  //TODO: Implement when bothered
  @Override
  public Iterator<T> iterator() {
    return new Iterator<T>() {

      @Override
      public boolean hasNext() {
        // TODO Auto-generated method stub
        return false;
      }

      @Override
      public T next() {
        // TODO Auto-generated method stub
        return null;
      }

      @Override
      public void remove() {
        //void
      }
      
    };
  }

}
