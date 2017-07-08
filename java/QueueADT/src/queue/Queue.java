package queue;
import java.util.Iterator;

import exception.QueueException;

public interface Queue<T> extends Iterable<T>{
  
  //Queue is empty
  public boolean isEmpty();

  //Add an element to the front of the queue
  public void enqueue(T element) throws QueueException;
  
  //Retrieve the front of the queue (Does NOT change the queue)
  public T getFront() throws QueueException;
  
  //Remove the front of the queue
  public T dequeue() throws QueueException;
  
  //Iterator over a queue
  public Iterator<T> iterator();

}
