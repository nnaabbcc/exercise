public class Fibonacci
{
  public static void printFibonacci(long number)
  {
    long num1 = 0;
    long num2 = 1;
    if (number >= 0)
      System.out.printf("Fibonacci of %d is: %d\n", num1, num1);
    if (number > 0)
      System.out.printf("Fibonacci of %d is: %d\n", num2, num2);
    if (number > 1)
    {
      for (long i = 2; i <= number; i++)
      {
        long sum = num1 + num2;
        System.out.printf("Fibonacci of %d is: %d\n", i, sum);
        num1 = num2;
        num2 = sum;
      }
    }
  }

  public static void main(String[] args)
  {
    if (args.length == 1)
    {
      long number = Long.parseLong(args[0]);
      printFibonacci(number);
    }
    else
    {
      System.out.println("Usage: Fibonacci <number>");
    }
  }
}
