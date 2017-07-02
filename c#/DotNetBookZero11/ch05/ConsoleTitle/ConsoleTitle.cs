
using System;

class ConsoleTitle
{
    static void Main()
    {
        string strOriginalTitle = Console.Title;
        Console.Title = "Please enter something:";
        Console.Write("Type anything and press Enter to quit program: ");
        Console.ReadLine();
        Console.Title = strOriginalTitle;
    }
}
