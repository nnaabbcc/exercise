import java.util.Scanner;

public class ScannerDemo_Next
{
  public static void main(String[] args)
  {
    Scanner scan = new Scanner(System.in);
    System.out.println("Use next to read:");
    if (scan.hasNext())
    {
      String str = scan.next();
      System.out.println("Got:" + str);
    }
  }
}
