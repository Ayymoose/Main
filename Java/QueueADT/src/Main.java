import java.util.Comparator;
import java.util.Iterator;
import java.util.PriorityQueue;

import queue.ArrayBasedQueue;
import queue.LinkedBasedQueue;
import queue.Queue;

public class Main {

  /**
   * @param args
   */
  public static void main(String[] args) {
    // TODO Auto-generated method stub
    
    Queue<String> linkedQueue = new LinkedBasedQueue<String>();
    Queue<Integer> arrayQueue = new ArrayBasedQueue<Integer>();
    
    
    Comparator<String> comparator = new Comparator<String>() {
      @Override
      public int compare(String o1, String o2) {
        return o1.length() - o2.length();
      }
     
    };
    
    PriorityQueue<String> priorityQueue = new PriorityQueue<String>(10,comparator);
    
    priorityQueue.add("Jon");
    priorityQueue.add("Bron");
    priorityQueue.add("Tyrion");
    priorityQueue.add("Cersei");

    linkedQueue.enqueue("Ayman");
    linkedQueue.enqueue("Jin");
    linkedQueue.enqueue("Jack");
    linkedQueue.enqueue("Polly");
    
    arrayQueue.enqueue(20);
    arrayQueue.enqueue(50);
    arrayQueue.enqueue(10);
    arrayQueue.enqueue(40);
    
    
    Iterator<String> it = priorityQueue.iterator();
    while (it.hasNext()) {
      System.out.println(it.next());
    }
    
    
  }

}
