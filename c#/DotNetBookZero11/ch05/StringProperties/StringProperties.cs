
using System;

class StringProperties
{
    static void Main()
    {
        Console.Write("Enter some text: ");
        string strText = Console.ReadLine();
        Console.WriteLine();
        Console.WriteLine("The text you entered has " + strText.Length + " characters.");
        if (strText.Length > 0)
        {
            Console.WriteLine("The first character is " + strText[0]);
            Console.WriteLine("The last character is " + strText[strText.Length - 1]);
        }
        Console.WriteLine();
    }
}