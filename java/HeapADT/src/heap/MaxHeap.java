package heap;

import java.util.Iterator;

import exception.HeapException;

public class MaxHeap<T extends Comparable<T>> implements Heap<T> {

  /*
   * Array implementation of Heap
   * Heap Axioms:
   * 
   * 1. parent(node[i]) = node[(i-1)/2]
   * 2. childLeft(node[i]) = node[2*i+1]
   * 3. childRight(node[i]) = node[2*i+2]
   */
  
  /*
   * Couldn't create auxiliary methods such as swap() and  parent() because of Java's lame pass by value
   * It cost me an hour because of this! !?0#!"!
   * 
   */
  
  
  private T[] heap;
  private int lastIndex;
  private static final int defaultInitialCapacity = 25;
  
  //Constructor
  public MaxHeap() {
    heap = (T[]) new Comparable[defaultInitialCapacity];
    lastIndex = 0;
  }
  
  @Override
  public boolean isEmpty() {
    return (lastIndex == 0);
  }
  
  @Override
  public void add(T element) throws HeapException {
    //Insert an element T into the Heap
    //We add it to the right most subtree at the bottom of the tree
    //Then trickle upwards , no need for recursion as we will use the parent property of a node
    
    //lastIndex <= capacity otherwise throw exception
    
    if (isEmpty()) {
      heap[0] = element;
 
    } else {
      //Add to the bottom of the tree (left)
      heap[lastIndex] = element;
      
      //Now trickle up the heap; 
      int index = lastIndex;
      
      while (index != 0) {        
        if (heap[(index - 1)/2].compareTo(heap[index]) < 0 ) {
          T elem = heap[(index - 1)/2];
          heap[(index - 1)/2] = heap[index];
          heap[index] = elem;
        }
        index = (index - 1) / 2;
      }
    }
    
    lastIndex++;
    
  }

  @Override
  public T removeMax() {

    //Remove a node from the heap
    T rootElement = heap[0];

    //If heap is not empty
    if (!isEmpty()) {

      //Swap the root for the right most node in the heap
      heap[0] = heap[lastIndex - 1];

      //Delete the node we swapped
      heap[lastIndex - 1] = null;

      lastIndex--;
      //Rebuild the heap to preserve the order
      heapRebuild(0);
      //Return the element we removed

    }

    return rootElement;
  }

  @Override
  public T getMax() {
    return (isEmpty() ? null : heap[0]);
  }
  
  
  //Rebuilds the heap to preserve the heap property
  private void heapRebuild(int root) {
    //Compare value in root with it's children
    //Property of MaxHeap says that the parent must be greater than (or equal) to it's children
    //Swap if the greater of the child
    //If a swap has occured we must check the children too
    
    int leftChild = 2*root + 1;
    int rightChild = leftChild + 1;
    
    //If root has children
    //Left child
    if (leftChild <= lastIndex && heap[leftChild] != null) {
      //Right child
      if (rightChild <= lastIndex && heap[rightChild] != null) {        
        //Right child "value" greater than left childs
        if (heap[rightChild].compareTo(heap[leftChild]) > 0) {
          leftChild = rightChild; 
        }        
      }      
      //If the root is smaller than it's child 
      if (heap[root].compareTo(heap[leftChild]) < 0) {
        //Swap them
        T element = heap[root];
        heap[root] = heap[leftChild];
        heap[leftChild] = element;
        
        //Rebuild the heap
        heapRebuild(leftChild);
      }
    }
    
  }

  @Override
  public Iterator<T> iterator() {
    
    //Performs breadth first traversal of the Heap
    
    return new Iterator<T>() {
      
      private int currentIndex = 0;

      @Override
      public boolean hasNext() {
        return currentIndex < lastIndex;
      }

      @Override
      public T next() {
        return heap[currentIndex++];
      }

      @Override
      public void remove() {
        //void
      }
      
    };
  }

}
