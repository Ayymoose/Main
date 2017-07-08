import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.SortedSet;
import java.util.TreeSet;

public class Main {

  
  
  public static int getLongestCycle(int i,int d) {
    List<Integer> remainders = new ArrayList<Integer>();
    //Compute i/d 
    StringBuilder sb = new StringBuilder();
    int r = 0;
    int cycle = 0;
    
    
    while (true) {

      while (d > i) {
        i *= 10;
        sb.append('0');
      }
      
    //  System.out.println(i);
      remainders.add(i);
      //System.out.print(i / d);
      sb.append(i / d);
      r -= d * (i / d);
      //r = i - d;
      

      cycle++;
      
      if (remainders.contains(i)) {
        System.out.println(sb.toString());
        return cycle;
      } else {
        System.out.println(Arrays.toString(remainders.toArray()));
        System.out.println(i);
      }
      i = r;

    }
    
 //   return 0;
  }
  
  public static void main(String[] args) {

   System.out.println(getLongestCycle(1,7));

  }

}
