import java.util.Scanner;

public class ScannerNumber
{
  public static void main(String[] args)
  {
    Scanner scan = new Scanner(System.in);
    int i = 0;
    float f = 0.0f;

    System.out.print("Integer: ");
    if (scan.hasNextInt())
    {
      i = scan.nextInt();
      System.out.println("Got: " + i);
    }
    else
    {
      System.out.println("Not a number!");
    }

    System.out.println("Float: ");
    if (scan.hasNextFloat())
    {
      f = scan.nextFloat();
      System.out.println("Got: " + f);
    }
    else
    {
      System.out.println("Not a float!");
    }
  }
}
