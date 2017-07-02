
using System;

class ShowEnviromentStuff
{
    static void Main()
    {
        Console.WriteLine("My Document is actaully " +
            Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments));
        Console.WriteLine();
        
        int msec = Environment.TickCount;
        Console.WriteLine("Windows has been running for " +
            msec + " milliseconds");
        Console.WriteLine("\t or " + (msec/3600000.0) + " hours");
        Console.WriteLine();
        
        Console.WriteLine("You are running " + Environment.OSVersion);
        Console.WriteLine("\t and .net framwork " + Environment.Version);
        Console.WriteLine();
    }
}