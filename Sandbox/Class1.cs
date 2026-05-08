using System;
using System.Runtime.InteropServices;

namespace Sandbox
{
    class ComponentA
    {
        [UnmanagedCallersOnly(EntryPoint = "SayIt")]
        public static void SayIt()
        {
            Console.WriteLine("Nasheeee");
        }
    };
}
