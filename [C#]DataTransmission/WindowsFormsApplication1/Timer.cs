using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace WindowsFormsApplication1
{
    static class Timer
    {
        private static Stopwatch watch;

        public static void Start()
        {
            watch = Stopwatch.StartNew();
        }

        public static double Stop()
        {
            watch.Stop();
            return watch.ElapsedMilliseconds;
        }

    }
}
