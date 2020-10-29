using System;

namespace Complex
{
    class Program
    {
        static void Main(string[] args)
        {
            TComplex U1 = new TComplex(-1.172,-0.084);
            Console.WriteLine($"{U1.GetPolar()}");
        }
    }
}