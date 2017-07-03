
using System;

class NumericFormatting
{
    static void Main()
    {
        Console.WriteLine("Currency    C3: " + Math.PI.ToString("C3"));
        Console.WriteLine("Exponential E3: " + Math.PI.ToString("E3"));
        Console.WriteLine("Fixed-Point F3: " + Math.PI.ToString("F3"));
        Console.WriteLine("General     G3: " + Math.PI.ToString("G3"));
        Console.WriteLine("Number      N3: " + Math.PI.ToString("N3"));
        Console.WriteLine("Percent     P3: " + Math.PI.ToString("P3"));
        Console.WriteLine("Round-Trip  R3: " + Math.PI.ToString("R3"));
        Console.WriteLine();
        Console.WriteLine("Fixed-Point F3: " + 12345678.9.ToString("F3"));
        Console.WriteLine("General     G3: " + 12345678.9.ToString("G3"));
        Console.WriteLine("Number      N3: " + 12345678.9.ToString("N3"));
        Console.WriteLine();
        Console.WriteLine("Decimal     D3: " + 55.ToString("D3"));
        Console.WriteLine("General     G3: " + 55.ToString("G3"));
        Console.WriteLine("Hexadecimal X3: " + 55.ToString("X3"));
    }
}