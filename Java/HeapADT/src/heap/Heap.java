package heap;

import java.util.Iterator;

import exception.HeapException;

public interface Heap<T extends Comparable<T>> extends Iterable<T> {
  
  //Heap<T extends Comparable<T>> Comparing Types within a Heap
  //Heap<T> extends Comparable<T> Comparing Heaps
  
  //Heap is empty?
  public boolean isEmpty();

  //Add element to heap
  public void add (T element) throws HeapException;
  
  //Remove element with maximum value
  public T removeMax();
  
  //Get element with maximum value
  public T getMax();
  
  //Iterator over a heap
  public Iterator<T> iterator();
  
}
