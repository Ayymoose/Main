import java.util.Arrays;


public final class NumberCrunch {
  
   private static final int[] pow10 = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
  
  /*
   * NumberCrunch library for number manipulation
   * Written by am5514
   */
   
  //Generates palindromes of length n
  public static int[] generatePalindromes(int n) {
    return null;
  }
   
   
  //Get the last n digits of an integer
  public static int[] getlastNDigits(int number,int n) {
    return null;
   }
   
  //Get the first n digits of an integer
  public static int[] getFirstNDigits(int number,int n) {
    //Details
    return null;
  }
   
  //Fast length of an integer using nested if statements
  public static int getLengthOf(int n) {
     //By Binary Search (Ah I don't know if it is now...)
     //{1, 2,  3,   4,    5,     6,      7,       8,        9,        10}
     //{1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
     if (n < 100000) {
       if (n < 1000) {
         if (n < 100) {
           if (n < 10) {
             return 1;
           } else {
             return 2;
           }
         } else {
           if (n < 1000) {
             return 3;
           } else {
             return 4;
           }
         }        
       } else {
         if (n < 10000) {
           return 4;
         } else {
           return 5;
         }
       }
     } else {
       if (n < 10000000) {
         if (n < 1000000) {
           return 6;
         } else {
           return 7;
         }
       } else {
         if (n < 100000000) {
           return 8;
         } else if (n < 1000000000){
           return 9;
         } else {
           return 10;
         }
       }
     }
  }
  
  //Reverse a number
  //1234 -> 4321
  public static int reverse(int n) {
    int numberLength = getLengthOf(n) - 1;
    int reverse = 0;
    while (n != 0) {
      reverse += (n % 10) * pow10[numberLength--];
      //Fast divide by 10
      n = (int) ((0x1999999AL * n) >> 32);
      //http://stackoverflow.com/questions/5558492/divide-by-10-using-bit-shifts?lq=1
      /*
          int32_t proc 
          mov    edx,1999999Ah    ; load 1/10 * 2^32
          imul   eax              ; edx:eax = dividend / 10 * 2 ^32
          mov    eax,edx          ; eax = dividend / 10
          ret
          int32_t endp
       */
    }
    return reverse;
  }
  
  //Returns the sum of the digits in a given integer
  public static int digitSum(int n) {
    int[] digits = getDigits(n);
    int sum = 0;
    int numberOfDigits = digits.length;
    for (int i=0; i<numberOfDigits; i++) {
      sum += digits[i];
    }
    return sum;
  }
  
  //Returns the digits of an integer as an array of ints
  //In the reverse order
  public static int[] getDigits(int n) {
    int numberOfDigits = getLengthOf(n);
    int[] digits = new int[numberOfDigits];
    for (int i=0; i<numberOfDigits; i++) {
      digits[i] = n % 10;
      n = (int) ((0x1999999AL * n) >> 32);
    }
    return digits;
  }
  
  //Returns the components of a number as an array of integers
  //E.g 1234 = [1000.200,30,4]
  public static int[] getComponents(int n) {
    int[] digits = getDigits(n);
    int numberOfDigits = digits.length;
    for (int i=0; i<numberOfDigits; i++) {
      digits[i] *= pow10[i];
    }
    return digits;
  }
  
  //Fast way to check if a number is even
  public static boolean isEven(int n) {
    return ((n & 0x1) == 0);
  }

  //Returns true iff k is a permutation of n
  // 1567,7561 -> True
  public static boolean isPermutationOf(int n, int k) {
    //Needs optimising
    int[] digitsN = getDigits(n);
    Arrays.sort(digitsN);
    int[] digitsK = getDigits(k);
    Arrays.sort(digitsK);
    return Arrays.equals(digitsN,digitsK);
  }
  
  //Returns true iff n is pandigital
  public static boolean isPandigital(int n) {
    
    if (getLengthOf(n) > 10) {
      return false;
    } else {
      //Gory details
      //Algorithm needed to check if a list contains a duplicate 
    }
    
    return false;
  }
  
  //Returns true iff n is palindromic
  public static boolean isPalindrome(int n) {
    //Quick and dirty
    return getDigits(n).equals(reverse(n));
  }

  //Returns true iff n is an increasing number (dn < dn-1 < dn-2 ... < d1)
  public static boolean isIncreasing(int n) {
    boolean increasing = true;
    int currentDigit = 0;
    while (n != 0) {
      currentDigit = n % 10;
      n = (int) ((0x1999999AL * n) >> 32);
      increasing &= (currentDigit >= n % 10);
    }
    return increasing;
  }

  //Returns true iff n is a decreasing number 
  public static boolean isDecreasing(int n) {
    boolean decreasing = true;
    int currentDigit = 0;
    while (n != 0) {
      currentDigit = n % 10;
      n = (int) ((0x1999999AL * n) >> 32);
      decreasing &= (n == 0 ? true : (currentDigit <= n % 10) );
    }
    return decreasing;
  }
  
  //Returns truee iff n is bouncy
  public static boolean isBouncy(int n) {
    return !(isIncreasing(n) | isDecreasing(n));
  }
  
}
