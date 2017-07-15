using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WindowsFormsApplication1;

namespace Haming
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Podaj ciag bitow: ");
            var a = Console.ReadLine();
            if (a.Length > 4)
            {
                Console.WriteLine("Za długi ciąg znaków!\nNacisnij Enter aby kontynuowac.");
                Console.ReadKey();
                return;
            }
            Console.WriteLine("Podaj bit do zanegowania: ");
            int diff = Int32.Parse(Console.ReadLine());

            Haming ham = new Haming(a, diff);
            
        }
    }

    public class Haming
    {
        private Dictionary<string, int> mgs;

        public Haming(string bity, int bitDoNegowania)
        {
            stringToDictonary(bity);
            Console.WriteLine("\nCiag przed negacja: ");
            printBits();

            neguj(bitDoNegowania+1);
            Console.WriteLine("\nNowy ciag binarny po negacji bitu {0}: ",bitDoNegowania);
            printBits();

            check();
            Console.WriteLine("\nCiag binarny po naprawie: ");
            printBits();
        }

        void stringToDictonary(string input)
        {
            List<int> buffor = new List<int>();
            foreach (var ch in input)
            {
                if (ch == '1')
                    buffor.Add(1);
                else
                    buffor.Add(0);
            }
            int x7, x6, x5, x4, x3, x2, x1;
            mgs = new Dictionary<string, int>();
            x7 = buffor[0];
            x6 = buffor[1];
            x5 = buffor[2];
            x3 = buffor[3];
            x4 = x5 ^ x6 ^ x7;
            x2 = x3 ^ x6 ^ x7;
            x1 = x3 ^ x5 ^ x7;
            mgs.Add("x1", x1);
            mgs.Add("x2", x2);
            mgs.Add("x3", x3);
            mgs.Add("x4", x4);
            mgs.Add("x5", x5);
            mgs.Add("x6", x6);
            mgs.Add("x7", x7);
        }
        void printBits()
        {
            Stack<int> stack = new Stack<int>();
            foreach (var mg in mgs)
                stack.Push(mg.Value);
            foreach (var i in stack)
                Console.Write(i);
        }
        void check()
        {
            int x1, x2, x4, x1_, x2_, x4_;
            double output;
            do
            {
                output = 0;
                x1 = mgs["x1"];
                x2 = mgs["x2"];
                x4 = mgs["x4"];

                x1_ = mgs["x3"] ^ mgs["x5"] ^ mgs["x7"];
                x2_ = mgs["x3"] ^ mgs["x6"] ^ mgs["x7"];
                x4_ = mgs["x5"] ^ mgs["x6"] ^ mgs["x7"];

                var x11 = x1 ^ x1_;
                var x12 = x2 ^ x2_;
                var x14 = x4 ^ x4_;
                output += x11*Math.Pow(2, 0);
                output += x12*Math.Pow(2, 1);
                output += x14*Math.Pow(2, 2);

                if(output >0)
                    neguj((int)output);

            } while (output != 0);

        }
        void neguj(int bit)
        {
            if (mgs["x" + bit] == 1)
                mgs["x" + bit] = 0;
            else
                mgs["x" + bit] = 1;
        }
    }
}
