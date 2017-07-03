
using System;

class Exponentiation
{
    static void Main()
    {
        Console.Write("Please enter the base: ");
        double number = Double.Parse(Console.ReadLine());
        
        Console.Write("Please enter the power: ");
        double power = Double.Parse(Console.ReadLine());
        
        Console.WriteLine(number + " to the " + power + " power equals " +
            Math.Pow(number, power));
    }
}