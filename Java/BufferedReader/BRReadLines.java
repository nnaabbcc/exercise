import java.io.*;

public class BRReadLines
{
  public static void main(String args[]) throws IOException
  {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    System.out.println("Enter lines of text.");
    System.out.println("Enter 'end' to quit.");

    // read char
    String str;
    do
    {
      str = br.readLine();
      System.out.println(str);
    } while (!str.equals("end"));
  }
}
