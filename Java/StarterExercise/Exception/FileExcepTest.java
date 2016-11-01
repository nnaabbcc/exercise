import java.io.*;

class FileExcepTest
{
  public static void main(String[] args)
  {
    if (args.length > 0)
    {
      for (String arg : args)
      {
        TestFile(arg);
      }
    }
    else
    {
      System.out.println("Usage: FileExcepTest <File Path List>");
    }
  }

  private static int TestFile(String fileName)
  {
    FileInputStream file;
    try
    {
      file = new FileInputStream(fileName);
      byte x = (byte) file.read();
    }
    catch (FileNotFoundException f)
    {
      f.printStackTrace();
      return -2;
    }
    catch (IOException i)
    {
      i.printStackTrace();
      return -1;
    }
    return 0;
  }
}
