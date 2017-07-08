import heap.Heap;
import heap.MaxHeap;

import java.util.Iterator;


public class Main {

  /**
   * @param args
   */
  public static void main(String[] args) {
    
    Heap<Integer> heap = new MaxHeap<Integer>();

    heap.add(14);
    heap.add(60);
    heap.add(128);
    heap.add(25);
    
    Iterator<Integer> it = heap.iterator();
    heap.removeMax();
    while (it.hasNext()) {
      System.out.println(it.next());
    }
    
  }

}
