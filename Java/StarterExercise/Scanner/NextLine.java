import java.util.Scanner;

public class NextLine
{
  public static void main(String[] args)
  {
    Scanner scan = new Scanner(System.in);
    System.out.println("Use nextLine to read:");
    if (scan.hasNextLine())
    {
      String str = scan.nextLine();
      System.out.println("Got: " + str);
    }
  }
}
