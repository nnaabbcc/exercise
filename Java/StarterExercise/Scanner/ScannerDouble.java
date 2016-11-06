import java.util.Scanner;

class ScannerDouble
{
  public static void main(String[] args)
  {
    Scanner scan = new Scanner(System.in);

    double sum = 0;
    int m = 0;

    while (scan.hasNextDouble())
    {
      double x = scan.nextDouble();
      m++;
      sum += x;
    }

    System.out.println("sum of " + m + " numbers: " + sum);
    System.out.println("Avarage is " + (sum/m));
  }
}
