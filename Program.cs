using System;
using System.Runtime.InteropServices;
// test
class Program
{
    [DllImport("sandbox", EntryPoint = "Add")]
    public static extern int Add(int a, int b);
    [DllImport("sandbox", EntryPoint = "Multiply")]
    public static extern int Multiply(int a, int b);

    static void Main()
    {
        int result = Add(3, 4);
        Console.WriteLine(result);
        result = Multiply(6, 7);
        Console.WriteLine(result);
    }
};
