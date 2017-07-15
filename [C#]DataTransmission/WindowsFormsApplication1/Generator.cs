using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.DataVisualization.Charting;

namespace WindowsFormsApplication1
{
    public struct Point
    {
        public double x;
        public double y;

        public Point(double x, double y)
        {
            this.x = x;
            this.y = y;
        }
    }

    public static class Gen
    {
//         Fs  - ilość próbek na sekundę
//         Ts  - czas trwania
//         F   - częstotliwość [Hz]
//         A   - amplituda
//         Phi - przesunięcie fazowe
//         c(t)- sygnał źródłowy
//         m(t)- sygnał nośny
//         z(t)- sygnał zmodulowany
//         W   - szerokość pasma

        #region Util

        public static Series PrepareSeries(string Nazwa)
        {
            Series temp = new Series(Nazwa);
            temp.ChartArea = "ChartArea1";
            temp.ChartType = SeriesChartType.Line;

            return temp;
        }

        public static Series PrepareSeries()
        {
            Series temp = new Series();
            temp.ChartArea = "ChartArea1";
            temp.ChartType = SeriesChartType.Line;

            return temp;
        }

        public static List<Point> PreparePoints()
        {
            var temp = new List<Point>();
            return temp;
        }

        private static double FindMax(IReadOnlyCollection<double> list)
        {
            if (list.Count == 0)
            {
                throw new InvalidOperationException("Empty list");
            }
            double maxAge = double.MinValue;
            foreach (double type in list)
            {
                if (type > maxAge)
                {
                    maxAge = type;
                }
            }
            return maxAge;
        }

        public static List<int> StringToBin(string str)
        {
            List<int> bin = new List<int>();

            foreach (var c in str)
            {
                int value = c;
                while (value != 0)
                {
                    bin.Add(value%2);
                    value /= 2;
                }
                while (bin.Count%8 != 0)
                {
                    bin.Add(0);
                }
            }

            return bin;
        }

        public static string BinToString(IReadOnlyCollection<int> Bin)
        {
            StringBuilder s = new StringBuilder();
            int licznik = 0;
            int suma = 0;
            foreach (var bit in Bin)
            {
                suma += bit*(int) Math.Pow(2, licznik);
                licznik++;

                if (licznik == 8)
                {
                    s.Append((char) suma);
                    suma = 0;
                    licznik = 0;
                }
            }
            return s.ToString();
        }

        public static Series GenSeriesFromPoints(List<Point> points)
        {
            var wykres = PrepareSeries();

            foreach (var point in points)
                wykres.Points.AddXY(point.x, point.y);

            return wykres;
        }

        public static double FindSignalFreq(List<Point> source, double Fs, double Ts)
        {
            var widmo = SpecFreq(source, Fs, Ts);
            double freq = double.NegativeInfinity;
            double maxFreq = double.NegativeInfinity;

            foreach (var point in widmo)
            {
                if (point.y > maxFreq)
                {
                    maxFreq = point.y;
                    freq = point.x;
                }
            }
            return freq;
        }

        #endregion

        public static Series Zadanie1(double Fs, double Ts, double F, double A, double Phi, string Nazwa)
        {
            //1500,2,18,0.7,(3/4)*Math.PI
            Series temp = PrepareSeries(Nazwa);

            double step = 1/Fs;
            long i = (long) (Ts/step);

            for (long x = 0; x < i; x++)
            {
                double y = A*Math.Sin((2*Math.PI*F*(x*step)) + Phi);
                temp.Points.AddXY(x*step, y);
            }

            return temp;
        }

        public static List<Point> Zadanie1(double Fs, double Ts, double F, double A, double Phi)
        {
            var wykres = PreparePoints();

            double step = 1/Fs;
            long i = (long) (Ts/step);

            for (long x = 0; x < i; x++)
            {
                double y = A*Math.Sin((2*Math.PI*F*(x*step)) + Phi);
                Point temp = new Point
                {
                    x = x*step,
                    y = y
                };
                wykres.Add(temp);
            }
            return wykres;
        }

        public static Series Zadanie2(double Fs, double Ts, double F1, double F2, string Nazwa)
        {
            //Generator.Zadanie2(2500, 1.5, 12, 30, 1, 0,);
            Series temp = PrepareSeries(Nazwa);

            double step = 1/Fs;
            long i = (long) (Ts/step);

            //z(t)
            double y = 0;
            long i2 = 0;
            double Fz = 0.67; // naciągna częstotliwość aby wyszedł łuk.
            double w1 = 2*Math.PI*F1;
            double w2 = 2*Math.PI*F2;

            for (long x = 0; x < i; x++)
            {
                if (x <= i/4)
                    y = y + step*((1/step)/(i/4));
                if (x > i/4 && x < i/2)
                    y = y - step*(1/step)/(i/4);
                if (x > i/2)
                {
                    y = Math.Sin(2*Math.PI*Fz*(i2*step));
                    i2++;
                }
                y = y*Math.Sin(w1*x/Fs)*Math.Cos(w2*x/Fs);
                temp.Points.AddXY(x*step, y*w1*w2);
            }

            return temp;
        }

        public static List<Point> Zadanie2(double Fs, double Ts, double F1, double F2)
        {
            //Generator.Zadanie2(2500, 1.5, 12, 30, 1, 0,);
            var wykres = PreparePoints();
            double step = 1/Fs;
            long i = (long) (Ts/step);

            //z(t)
            double y = 0;
            long i2 = 0;
            double Fz = 0.67; // naciągna częstotliwość aby wyszedł łuk.
            double Az = 1;
            double w1 = 2*Math.PI*F1;
            double w2 = 2*Math.PI*F2;

            for (long x = 0; x < i; x++)
            {
                if (x <= i/4)
                    y = y + step*((1/step)/(i/4));
                if (x > i/4 && x < i/2)
                    y = y - step*(1/step)/(i/4);
                if (x > i/2)
                {
                    y = Az*Math.Sin(2*Math.PI*Fz*(i2*step));
                    i2++;
                }
                y = y*Math.Sin(w1*x/Fs)*Math.Cos(w2*x/Fs);

                Point temp = new Point
                {
                    x = x*step,
                    y = y*w1*w2
                };
                wykres.Add(temp);
            }

            return wykres;
        }

        public static Series Zadanie3(double Fs, double Ts, double F, double k, string Nazwa)
        {
            //Fs 2500 Ts 1.5 F 5
            Series Wykres = PrepareSeries(Nazwa);

            double step = 1/Fs;
            double i = (long) (Ts/step);

            for (int x = 0; x < i; x++)
            {
                double suma = 0;
                for (double ki = 1; ki <= k; ki++)
                {
                    suma += 1/(2*ki - 1)*Math.Sin((2*ki - 1)*2*Math.PI*x*F/Fs);
                }
                Wykres.Points.AddXY(0 + x*step, (4/Math.PI)*suma);
            }
            return Wykres;
        }

        public static List<Point> Zadanie3(double Fs, double Ts, double F, double k)
        {
            //Fs 2500 Ts 1.5 F 5
            var wykres = PreparePoints();

            double step = 1/Fs;
            double i = (long) (Ts/step);

            for (int x = 0; x < i; x++)
            {
                double suma = 0;
                for (double ki = 1; ki <= k; ki++)
                {
                    suma += 1/(2*ki - 1)*Math.Sin((2*ki - 1)*2*Math.PI*x*F/Fs);
                }

                Point temp = new Point
                {
                    x = x*step,
                    y = (4/Math.PI)*suma
                };
                wykres.Add(temp);
            }
            return wykres;
        }

        public static Series SpecFreq(List<Point> x, double Fs, double Ts, string Nazwa)
        {
            Series Wykres = PrepareSeries(Nazwa);
            int N = x.Count();
            double fi = 0;

            double[] a = new double[N];
            double[] b = new double[N];
            double[] z = new double[N];
            double[] fiX = new double[N/2];

            for (int k = 0; k < N; k++)
            {
                for (int n = 0; n < N; n++)
                {
                    fi = 2*Math.PI*n*k/N;
                    a[k] += x[n].y*Math.Cos(fi);
                    b[k] += x[n].y*Math.Sin(-fi);
                }
                z[k] = Math.Sqrt(Math.Pow(a[k], 2) + Math.Pow(b[k], 2));
            }

            for (int i = 0; i < (N/2) - 1; i++)
            {
                Wykres.Points.AddXY(i*Fs/N, z[i]);
            }

            return Wykres;
        }

        public static List<Point> SpecFreq(List<Point> x, double Fs, double Ts)
        {
            var Wykres = PreparePoints();
            int N = x.Count();
            double fi = 0;

            double[] a = new double[N];
            double[] b = new double[N];
            double[] z = new double[N];
            double[] fiX = new double[N / 2];

            for (int k = 0; k < N; k++)
            {
                for (int n = 0; n < N; n++)
                {
                    fi = 2 * Math.PI * n * k / N;
                    a[k] += x[n].y * Math.Cos(fi);
                    b[k] += x[n].y * Math.Sin(-fi);
                }
                z[k] = Math.Sqrt(Math.Pow(a[k], 2) + Math.Pow(b[k], 2));
            }

            for (int i = 0; i < (N / 2)-1; i++)
            {
                Wykres.Add(new Point(i*Fs/N,z[i]));
//                Wykres.Points.AddXY(i * Fs / N, z[i]);
            }

            return Wykres;
        }

        public static Series SpecPower(List<Point> z, double Fs, string Nazwa)
        {
            var Wykres = PrepareSeries(Nazwa);
            int N = z.Count();
            double fi = 0;

            double[] a = new double[N];
            double[] b = new double[N];
            double[] NewZ = new double[N];
            var XD = new List<double>();

            for (int k = 0; k < N; k++)
            {
                for (int n = 0; n < N; n++)
                {
                    fi = 2*Math.PI*n*k/N;
                    a[k] += z[n].y*Math.Cos(fi);
                    b[k] += z[n].y*Math.Sin(-fi);
                }
                NewZ[k] = Math.Pow(a[k], 2) + Math.Pow(b[k], 2);
                XD.Add(10*Math.Log10(NewZ[k]));
            }

            for (int i = 0; i < N/2; i++)
            {
                double sd = XD[i] - FindMax(XD);
//                Wykres.Points.AddXY(i * Fs / N, sd);
                Wykres.Points.AddXY(z[i].x, sd);
            }

            return Wykres;
        }

        public static List<Point> ModAM(List<Point> c, double Fs, double Ts, double fm, double Kam, double phi)
        {
            var wykres = PreparePoints();

            double step = 1/Fs;
            int i = (int) (Ts/step);
            
            for (int t = 0; t < i; t++)
            {
                double z = (1 + Kam*c[t].y)*Math.Sin(2*Math.PI*fm*t/Fs + phi);
                wykres.Add(new Point(c[t].x, z));
            }

            return wykres;
        }

        public static List<Point> ModPM(List<Point> c, double Fs, double Ts, double fm, double Kpm, double am)
        {
            var wykres = PreparePoints();

            double step = 1/Fs;
            int i = (int) (Ts/step);

            for (int t = 0; t < i; t++)
            {
                double z = am*Math.Sin(2*Math.PI*fm* t/Fs + Kpm*c[t].y);
                wykres.Add(new Point(c[t].x, z));
            }

            return wykres;
        }

        public static Series ModASK1(List<int> c, double Fs, double Ts, double A, string Nazwa)
        {
            Series wykres = PrepareSeries(Nazwa);

            double step = 1/Fs;
            int i = (int) (Ts/step);
            int M = c.Count;

            double Tb = Ts/M;
            double f = 1 / Tb;
            double Tbprobka = Ts*Fs/M;

            for (int t = 0; t < i; t++)
            {
                double z;
                //Tb w próbkach w for Tb = Ts*Fs/ M   [Tb w próbkach]

                if (c[(int)(t/Tbprobka)] == 0)
                    z = 0;
                else
                    z = A*Math.Sin(2*Math.PI*f*t/Fs);
                wykres.Points.AddXY(t*step, z);

            }

            return wykres;
        }

        public static List<Point> ModASK1(List<int> c, double Fs, double Ts, double A)
        {
            var wykres = PreparePoints();

            double step = 1 / Fs;
            int i = (int)(Ts / step);
            int M = c.Count;

            double Tb = Ts / M;
            double f = 1 / Tb;
            double Tbprobka = Ts * Fs / M;

            double z;
            for (int t = 0; t < i; t++)
            {
                if (c[(int)(t / Tbprobka)] == 0)
                    z = 0;
                else
                    z = A * Math.Sin(2 * Math.PI * f * t / Fs);
                wykres.Add(new Point(t*step, z));

            }

            return wykres;
        }

        public static Series ModASK2(List<int> c, double Fs, double Ts, double A1, double A2, string Nazwa)
        {
            Series wykres = PrepareSeries(Nazwa);

            double step = 1/Fs;
            int i = (int) (Ts/step);
            int N = c.Count;


            double Tb = Ts / N;
            double f = 1 / Tb;
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 0)
                    z = A1*Math.Sin(2*Math.PI*f*t / Fs); // po prawej to jest już przekształcony wzór m(t)
                else
                    z = A2*Math.Sin(2*Math.PI*f*t / Fs); // po prawej to jest już przekształcony wzór m(t)
                wykres.Points.AddXY(t*step, z);
            }

            return wykres;
        }

        public static List<Point> ModASK2(List<int> c, double Fs, double Ts, double A1, double A2)
        {
            var wykres = PreparePoints();

            double step = 1 / Fs;
            int i = (int)(Ts / step);
            int N = c.Count;


            double Tb = Ts / N;
            double f = 1 / Tb;
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 0)
                    z = A1 * Math.Sin(2 * Math.PI * f * t / Fs); // po prawej to jest już przekształcony wzór m(t)
                else
                    z = A2 * Math.Sin(2 * Math.PI * f * t / Fs); // po prawej to jest już przekształcony wzór m(t)
                wykres.Add(new Point(t*step,z));
//                wykres.Points.AddXY(t * step, z);
            }

            return wykres;
        }

        public static Series ModFSK(List<int> c, double Fs, double Ts, double A, string Nazwa)
        {
            Series wykres = PrepareSeries(Nazwa);

            double step = 1/Fs;
            int i = (int) (Ts/step);
            int N = c.Count;

            double Tb = Ts/N;
            double f1 = N/Fs + 1/Tb;
            double f2 = N/Fs + 2/Tb;
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 0)
                    z = A*Math.Sin(2*Math.PI*f1*t / Fs);
                else
                    z = A*Math.Sin(2*Math.PI*f2*t / Fs);
                wykres.Points.AddXY(t*step, z);
            }

            return wykres;
        }

        public static List<Point> ModFSK(List<int> c, double Fs, double Ts, double A)
        {
            var wykres = PreparePoints();

            double step = 1 / Fs;
            int i = (int)(Ts / step);
            int N = c.Count;

            double Tb = Ts / N;
            double f1 = N / Fs + 1 / Tb;
            double f2 = N / Fs + 2 / Tb;
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 0)
                    z = A * Math.Sin(2 * Math.PI * f1 * t / Fs);
                else
                    z = A * Math.Sin(2 * Math.PI * f2 * t / Fs);
                wykres.Add(new Point(t*step, z));
//                wykres.Points.AddXY(t * step, z);
            }

            return wykres;
        }

        public static Series ModPSK(List<int> c, double Fs, double Ts, double A, string Nazwa)
        {
            Series wykres = PrepareSeries(Nazwa);

            double step = 1/Fs;
            int i = (int) (Ts/step);
            int N = c.Count;

            double Tb = Ts/N;
            double f = i/Fs*1/Tb;
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 1)
                    z = A*Math.Sin(2*Math.PI*f*t/Fs); // po prawej to jest już przekształcony wzór m(t)
                else
                    z = -A*Math.Sin(2*Math.PI*f*t/Fs); // po prawej to jest już przekształcony wzór m(t)
                wykres.Points.AddXY(t*step, z);
            }

            return wykres;
        }

        public static List<Point> ModPSK(List<int> c, double Fs, double Ts, double A)
        {
            var wykres = PreparePoints();

            double step = 1 / Fs;
            int i = (int)(Ts / step);
            int N = c.Count;

            double Tb = Ts / N;
            double f = (i / Fs * 1 / Tb)/2; // /2 => aby był jeden okres na 1 bit
            double Tbprobka = Ts * Fs / N;

            for (int t = 0; t < i; t++)
            {
                double z;
                if (c[(int)(t / Tbprobka)] == 1)
                    z = A * Math.Sin(2 * Math.PI * f * t / Fs); // po prawej to jest już przekształcony wzór m(t)
                else
                    z = -A * Math.Sin(2 * Math.PI * f * t / Fs); // po prawej to jest już przekształcony wzór m(t)
                wykres.Add(new Point(t*step, z));
//                wykres.Points.AddXY(t * step, z);
            }

            return wykres;
        }
        
        public static Series DemodulatorASK(List<Point> z,int SignalN, double Fs, double Ts, double A, int faza, string Nazwa)
        {
            var outputSignal = new List<int>();
            var wykres = PrepareSeries(Nazwa);
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);

            var x = new List<Point>();
            //            double freq = FindSignalFreq(z, Fs, Ts);
            double Tb = Ts / SignalN;
            double freq = 1 / Tb; // /2 => aby był jeden okres na 1 bit

            for (int t = 0; t < i; t++)
            {
                double nosna = A * Math.Sin(2 * Math.PI * freq * t/Fs);
                x.Add(new Point(t*step, z[t].y * nosna));
                if(faza == 1)
                   wykres.Points.AddXY(t*step, z[t].y*nosna);
            }
            var p = new List<Point>();
            double Tbprobka = Ts * Fs / SignalN;
            double sum = 0;
            int k = 0;
            for (int t = 0; t < N; t++)
            {
                sum += x[t].y;
                p.Add(new Point(z[t].x,sum));
                if ((int)((t+1) / Tbprobka) == k)
                {
                    sum = 0;
                    k++;
                }
                if(faza == 2)
                    wykres.Points.AddXY(p[t].x, p[t].y);
            }

            Boolean status = false;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                if (p[(int)t].y > 0.5)
                    status = true;
                else
                    status = false;
                if ((int)((t+1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if(status == true)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    status = false;
                    k++;
                }
            }

            return wykres;
        }

        public static List<int> DemodulatorASK(List<Point> z, int SignalN, double Fs, double Ts, double A)
        {
            var outputSignal = new List<int>();
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);

            var x = new List<Point>();
//            double freq = FindSignalFreq(z, Fs, Ts);
            double Tb = Ts / SignalN;
            double freq =  1 / Tb; // /2 => aby był jeden okres na 1 bit


            //Faza mnożenia aby uzyskać sygnał tylko na górnej połowie.
            for (int t = 0; t < i; t++)
            {
                double nosna = A * Math.Sin(2 * Math.PI * freq * t / Fs);
                x.Add(new Point(t * step, z[t].y * nosna));
            }

            //Faza sumowania wykresów.
            var p = new List<Point>();
            var p2 = new List<double>();
            double Tbprobka = Ts * Fs / SignalN;
            double sum = 0;
            int k = 0;
            for (int t = 0; t < N; t++)
            {
                sum += x[t].y;
                p.Add(new Point(z[t].x, sum));
                p2.Add(sum);
                if ((int)((t + 1) / Tbprobka) == k)
                {
                    sum = 0;
                    k++;
                }
            }

            var max = FindMax(p2);
            //Faza deszyfrowania wyników na bity.
            var status = false;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                if (p[(int)t].y > max*0.75)
                    status = true;
                else
                    status = false;
                if ((int)((t + 1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if (status == true)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    status = false;
                    k++;
                }
            }

            return outputSignal;
        }

        public static Series DemodulatorFSK(List<Point> z, int SignalN, double Fs, double Ts, double A, string Nazwa)
        {
            var outputSignal = new List<int>();
            var wykres = PrepareSeries(Nazwa);
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);

            double Tb = Ts / SignalN;
            double FreqL = SignalN / Fs + 1 / Tb;
            double FreqH = SignalN / Fs + 2 / Tb;


            var p = new List<Point>();
            double Tbprobka = Ts * Fs / SignalN;

            int k = 0;
            double sumL=0;
            double sumH=0;
            for (int t = 0; t < N; t++)
            {
                sumL += z[t].y * A*Math.Sin(2*Math.PI*FreqL*t/Fs);
                sumH += z[t].y * A*Math.Sin(2*Math.PI*FreqH*t/Fs);

                p.Add(new Point(z[t].x,sumH-sumL));
                if ((int)((t + 1) / Tbprobka) == k)
                {
                    sumL = 0;
                    sumH = 0;
                    k++;
                }
                wykres.Points.AddXY(p[t].x, p[t].y);
            }

            int sumaH = 0;
            int sumaL = 0;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                if (p[t].y > 0)
                    sumaH++;
                else
                    sumaL++;

                if ((int)((t + 1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if (sumaH > sumaL)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    k++;
                    sumaH = 0;
                    sumaL = 0;
                }
            }

            return wykres;
        }

        public static List<int> DemodulatorFSK(List<Point> z, int SignalN, double Fs, double Ts, double A)
        {
            var outputSignal = new List<int>();
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);

            double Tb = Ts / SignalN;
            double FreqL = SignalN / Fs + 1 / Tb;
            double FreqH = SignalN / Fs + 2 / Tb;


            var p = new List<Point>();
            double Tbprobka = Ts * Fs / SignalN;

            int k = 0;
            double sumL = 0;
            double sumH = 0;
            for (int t = 0; t < N; t++)
            {
                sumL += z[t].y * A * Math.Sin(2 * Math.PI * FreqL * t / Fs);
                sumH += z[t].y * A * Math.Sin(2 * Math.PI * FreqH * t / Fs);

                p.Add(new Point(z[t].x, sumH - sumL));
                if ((int)((t + 1) / Tbprobka) == k)
                {
                    sumL = 0;
                    sumH = 0;
                    k++;
                }
            }

            int sumaH = 0;
            int sumaL = 0;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                if (p[t].y > 0)
                    sumaH++;
                else
                    sumaL++;

                if ((int)((t + 1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if (sumaH > sumaL)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    k++;
                    sumaH = 0;
                    sumaL = 0;
                }
            }

            return outputSignal;
        }

        public static Series DemodulatorPSK(List<Point> z, int SignalN, double Fs, double Ts, double A, int faza, string Nazwa)
        {
            var wykres = PrepareSeries(Nazwa);
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);


            var x = new List<Point>();
            double Tb = Ts / SignalN;
            double freq = (i / Fs * 1 / Tb) / 2; // /2 => aby był jeden okres na 1 bit

            for (int t = 0; t < i; t++)
            {
                double nosna = A * Math.Sin(2 * Math.PI * freq * t / Fs);
                x.Add(new Point(t * step, z[t].y * nosna));
                if (faza == 1)
                    wykres.Points.AddXY(t * step, z[t].y * nosna);
            }


            var p = new List<Point>();
            double Tbprobka = Ts * Fs / SignalN;
            double sum = 0;
            int k = 0;
            for (int t = 0; t < N; t++)
            {
                sum += x[t].y;
                p.Add(new Point(z[t].x, sum));
                if ((int)((t + 1) / Tbprobka) == k)
                {
                    sum = 0;
                    k++;
                }
                if (faza == 2)
                    wykres.Points.AddXY(p[t].x, p[t].y);
            }


            var outputSignal = new List<int>();
            double suma = 0;
            Boolean status = false;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                suma += p[t].y;
                if ((int)((t + 1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if (suma>0)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    k++;
                    suma = 0;
                }
            }

            return wykres;
        }

        public static List<int> DemodulatorPSK(List<Point> z, int SignalN, double Fs, double Ts, double A)
        {
            var outputSignal = new List<int>();
            int N = z.Count;
            double step = 1 / Fs;
            int i = (int)(Ts / step);

            var x = new List<Point>();
            double Tb = Ts / SignalN;
            double freq = (i / Fs * 1 / Tb) / 2; // /2 => aby był jeden okres na 1 bit

            for (int t = 0; t < i; t++)
            {
                double nosna = A * Math.Sin(2 * Math.PI * freq * t / Fs);
                x.Add(new Point(t * step, z[t].y * nosna));
            }
            var p = new List<Point>();
            double Tbprobka = Ts * Fs / SignalN;
            double sum = 0;
            int k = 0;
            for (int t = 0; t < N; t++)
            {
                sum += x[t].y;
                p.Add(new Point(z[t].x, sum));
                if ((int)((t + 1) / Tbprobka) == k)
                {
                    sum = 0;
                    k++;
                }
            }
            double suma = 0;
            k = 1;
            for (int t = 0; t < N; t++)
            {
                suma += p[t].y;
                if ((int)((t + 1) / Tbprobka) == k) // kolejne bity w sygnale 
                {
                    if (suma > 0)
                        outputSignal.Add(1);
                    else
                        outputSignal.Add(0);
                    k++;
                    suma = 0;
                }
            }

            return outputSignal;
        }

        public static List<Point> GenSqWave(double Fs, double Ts, double F, double A)
        {
            var wave = PreparePoints();
            double step = 1/Fs;
            int i = (int) (Ts/step);
            double z = 0;

            for (int t = 0; t < i; t++)
            {
                double y = Math.Sin((2*Math.PI*F*(t/Fs)));
                if (y > 0)
                    z = 1 * A;
                else
                    z = 0;
                wave.Add(new Point(t*step, z));
            }
            return wave;
        }

        public static List<Point> GenSqWaveFromPoints(List<int> points, double Fs, double Ts, double F, double A)
        {
            var wave = PreparePoints();
            double step = 1 / Fs;
            int i = (int)(Ts / step);
            double z = 0;
            double Tbprobka = Ts * Fs / points.Count;
            for (int t = 0; t < i; t++)
            {
//                double y = Math.Sin((2 * Math.PI * F * (t / Fs)));
                if (points[(int)(t / Tbprobka)] == 1)
                    z = 1 * A;
                else
                    z = 0;
                wave.Add(new Point(t * step, z));
            }
            return wave;
        }

        public static List<int> Haming(List<int> points, double Fs, double Ts, double F, double A)
        {
            
            return new List<int>();
        }
    }
}
