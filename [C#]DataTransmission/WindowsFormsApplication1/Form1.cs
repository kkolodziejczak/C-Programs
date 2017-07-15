using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private int NumberLevel1 = 1;
        private int NumberLevel2 = 1;

        public Form1()
        {
            InitializeComponent();
        }


        #region Laboratoria

        private void Laboratoria1()
        {
            Plot test = new Plot(chart1);

            double Ts = 2;//sec
            double Fs = 1500;//Hz
            double F = 18;//Hz
            double A = 0.7;
            double Phi = (3 / 4) * Math.PI;
            string NazwaFunkcji;
            double F1;
            double F2;
            int k;
            switch (NumberLevel2)
            {
                case 1:
                    NazwaFunkcji = "Ts = " + Ts
                       + " Fs = " + Fs + " F = " + F + " A = " + A
                       + " Phi = " + Phi;
                    test.AddSeiresToPlot(Gen.Zadanie1(Fs, Ts, F, A, Phi, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 1. Sinusoida";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 2:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 10;
                    F2 = 15;

                    NazwaFunkcji = "w1(" + F1 + "Hz) < w2(" + F2 + "Hz)";

                    test.AddSeiresToPlot(Gen.Zadanie2(Fs, Ts, F1, F2, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 2.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 3:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 15;
                    F2 = 10;

                    NazwaFunkcji = "w1(" + F1 + "Hz) > w2(" + F2 + "Hz)";
                
                    test.AddSeiresToPlot(Gen.Zadanie2(Fs, Ts, F1, F2, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 2.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 4:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 15;
                    F2 = 15;

                    NazwaFunkcji = "w1(" + F1 + "Hz) = w2(" + F2 + "Hz)";

                    test.AddSeiresToPlot(Gen.Zadanie2(Fs, Ts, F1, F2, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 2.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 5:
                    k = 8;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 5;//Hz
                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString();
                    test.AddSeiresToPlot(Gen.Zadanie3(Fs, Ts, F, k, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 3.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 6:
                    k = 16;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 5;//Hz
                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString();
                    test.AddSeiresToPlot(Gen.Zadanie3(Fs, Ts, F, k, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 3.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                case 7:
                    k = 32;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 5;//Hz
                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString();
                    test.AddSeiresToPlot(Gen.Zadanie3(Fs, Ts, F, k, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 3.";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    test.PlotChart();
                    break;
                default:
                    break;
            }
        }

        private void Laboratoria2()
        {
            Plot Wykres = new Plot(chart1);
            double Ts = 2;//sec
            double Fs = 1500;//Hz
            double F = 180;//Hz
            double A = 0.7;
            double Phi = (3 / 4) * Math.PI;
            string NazwaFunkcji;
            double F1 = 500;
            double F2 = 500;
            int k;

            switch (NumberLevel2)
            {
                case 1:
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi;
                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(Gen.Zadanie1(Fs, Ts, F, A, Phi), Fs, Ts, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Zadanie 1. Widmo sinusoidy";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    Wykres.PlotChart();
                    break;
                case 2:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 250;
                    F2 = 500;

                        NazwaFunkcji = "w1(" + F1 + "Hz) < w2(" + F2 + "Hz)";
                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie2(Fs, Ts, F1, F2), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 2. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:"+Timer.Stop() + " ms";
                    break;
                case 3:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 500;
                    F2 = 250;

                        NazwaFunkcji = "w1(" + F1 + "Hz) > w2(" + F2 + "Hz)";

                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie2(Fs, Ts, F1, F2), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 2. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    break;
                case 4:
                    Ts = 1.5;
                    Fs = 2500;
                    F1 = 500;
                    F2 = 500;

                        NazwaFunkcji = "w1(" + F1 + "Hz) = w2(" + F2 + "Hz)";

                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie2(Fs, Ts, F1, F2), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 2. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    break;
                case 5:
                    k = 8;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 10;//Hz
                    
                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString() +"Hz";
                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie3(Fs, Ts, F, k), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 3. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    break;
                case 6:
                    k = 16;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 10;//Hz

                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString() + "Hz";
                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie3(Fs, Ts, F, k), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 3. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    break;
                case 7:
                    k = 32;
                    Ts = 1.5;//sec
                    Fs = 2500;//Hz
                    F = 10;//Hz

                    NazwaFunkcji = "k = " + k.ToString() + " F = " + F.ToString() + "Hz";
                    Timer.Start();
                    Wykres.AddSeiresToPlot(Gen.SpecFreq(
                                            Gen.Zadanie3(Fs, Ts, F, k), Fs, Ts, NazwaFunkcji));
                    Wykres.PlotChart();
                    chart1.Titles["Title1"].Text = "Zadanie 3. Widmo";
                    chart1.Titles["Title2"].Text = "f(Hz)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji + " \ntime:" + Timer.Stop() + " ms";
                    break;
            }

            
        }

        private void Laboratoria3()
        {
            Plot Wykres = new Plot(chart1);
            double Ts = 2;//sec
            double Fs = 1500;//Hz
            double F = 70;//Hz
            double A = 0.7;
            double Phi = (3 / 4) * Math.PI;
            string NazwaFunkcji;
            double Kam = 0;
            double Kpm = 0;
            double am = 0;
            List<Point> Wiadomosc;
            List<Point> wiadomoscZmodulowana;
            switch (NumberLevel2)
            {
                case 1:
                    Kam = 0.3;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kam = " +Kam;

                    Wiadomosc = Gen.Zadanie1(Fs,Ts,F,A,Phi);
                    wiadomoscZmodulowana = Gen.ModAM(Wiadomosc, Fs, Ts, 200, Kam, Phi);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana,Fs,NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji AM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 2:
                    Kam = 0.9;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kam = " + Kam;

                    Wiadomosc = Gen.Zadanie1(Fs, Ts, F, A, Phi);
                    wiadomoscZmodulowana = Gen.ModAM(Wiadomosc, Fs, Ts, 200, Kam, Phi);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana, Fs, NazwaFunkcji));
//                    Wykres.AddSeiresToPlot(Gen.SpecFreq(wiadomoscZmodulowana, Fs, Ts, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji AM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 3:
                    Kam = 13;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kam = " + Kam;

                    Wiadomosc = Gen.Zadanie1(Fs, Ts, F, A, Phi);
                    wiadomoscZmodulowana = Gen.ModAM(Wiadomosc, Fs, Ts, 200, Kam, Phi);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana, Fs, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji AM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;

                case 4:
                    Kpm = 0.5;
                    am = 0.5; 
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kpm = " + Kpm;

                    Wiadomosc = Gen.Zadanie1(Fs, Ts, F, A, Phi);
                    wiadomoscZmodulowana = Gen.ModPM(Wiadomosc, Fs, Ts, 400, Kpm, am);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana, Fs, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji PM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 5:
                    Kpm = 1;
                    am = 0.5;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kpm = " + Kpm;

                    Wiadomosc = Gen.Zadanie1(Fs, Ts, F, A, Phi);
                    wiadomoscZmodulowana = Gen.ModPM(Wiadomosc, Fs, Ts, 400, Kpm, am);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana, Fs, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji PM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 6:
                    Kpm = 22;
                    am = 0.5;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F + " A = " + A
                                          + " Phi = " + Phi + " Kpm = " + Kpm;

                    Wiadomosc = Gen.Zadanie1(Fs, Ts, F, A, Phi);
                    wiadomoscZmodulowana = Gen.ModPM(Wiadomosc, Fs, Ts, 400, Kpm, am);

                    Wykres.AddSeiresToPlot(Gen.SpecPower(wiadomoscZmodulowana, Fs, NazwaFunkcji));
                    chart1.Titles["Title1"].Text = "Widmo Modulacji PM";
                    chart1.Titles["Title2"].Text = "dB";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
            }
        }

        private void Laboratoria4()
        {

            Plot Wykres = new Plot(chart1);
            double Ts = 1;//sec
            double Fs = 1500;//Hz
            double F = 1;//Hz
            string NazwaFunkcji;
            double A1 = 0;
            double A2 = 0;

            var wiadomosc = Gen.StringToBin("Ulaood");
            StringBuilder str = new StringBuilder();
            foreach (var i in wiadomosc)
            {
                str.Append(i);
            }
            switch (NumberLevel2)
            {
                case 1: //ASK1
                    A1 = 1;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n" + str.ToString();

//                    Wykres.AddSeiresToPlot(Gen.ModASK1(wiadomosc,Fs,Ts,A1,"ModulacjaASK1"));
                    Wykres.AddSeiresToPlot(Gen.SpecPower(Gen.ModASK1(wiadomosc, Fs, Ts, A1), Fs, ""));
                    chart1.Titles["Title1"].Text = "Modulacja ASK1";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 2: // ASK2
                    A1 = 1;
                    A2 = 2;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A1 = " + A1 + " A2 = " + A2 + "\n" + str.ToString();
//                    Wykres.AddSeiresToPlot(Gen.ModASK2(wiadomosc, Fs, Ts, A1, A2, "ModulacjaASK2"));
                    Wykres.AddSeiresToPlot(Gen.SpecPower(Gen.ModASK2(wiadomosc, Fs, Ts, A1,A2), Fs, ""));
                    chart1.Titles["Title1"].Text = "Modulacja ASK2";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 3: //FSK
                    A1 = 1;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n" + str.ToString();

//                    Wykres.AddSeiresToPlot(Gen.ModFSK(wiadomosc, Fs, Ts ,A1, "ModulacjaFSK"));
                    Wykres.AddSeiresToPlot(Gen.SpecPower(Gen.ModFSK(wiadomosc, Fs, Ts, A1), Fs, ""));
                    chart1.Titles["Title1"].Text = "Modulacja FSK";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 4: //PSK
                    A1 = 1;
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n" + str.ToString();

//                    Wykres.AddSeiresToPlot(Gen.ModPSK(wiadomosc, Fs, Ts, A1, "ModulacjaPSK"));
                    Wykres.AddSeiresToPlot(Gen.SpecPower(Gen.ModPSK(wiadomosc, Fs, Ts, A1), Fs, ""));
                    chart1.Titles["Title1"].Text = "Modulacja PSK";
                    chart1.Titles["Title2"].Text = "";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 5: //SquareWave
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " F = " + F;

                    F = 5;

                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(Gen.GenSqWave(Fs,Ts,F,1)));
                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(Gen.GenSqWave(Fs,Ts,2*F, 0.7)));
                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(Gen.GenSqWave(Fs,Ts,4*F, 0.4)));

                    chart1.Titles["Title1"].Text = "Square Wave";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
            }
        }

        private void Laboratoria5()
        {
            Plot Wykres = new Plot(chart1);
            double Ts = 2;//sec
            double Fs = 1500;//Hz
            double F = 1;//Hz
            string NazwaFunkcji;
            double A1 = 0;
            double A2 = 0;
            string wiadomoscString = "Zadanie";
            var wiadomosc = Gen.StringToBin(wiadomoscString);
            StringBuilder str = new StringBuilder();
            foreach (var i in wiadomosc)
            {
                str.Append(i);
            }
            switch (NumberLevel2)
            {
                case 1: //demodulatorASK1
                    A1 = 1;
                    var ztASK = Gen.ModASK1(wiadomosc, Fs, Ts, A1*70);
//                    var ztASK = Gen.ModASK2(wiadomosc, Fs, Ts, A1, A1+1);
                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(ztASK));
                    
                    //Pierwszy etap demodulacji
                    Wykres.AddSeiresToPlot(Gen.DemodulatorASK(ztASK, wiadomosc.Count, Fs, Ts, A1*140,1, "DemodulacjaAsk1"));
                    //Drugi etap demodulacji
                    Wykres.AddSeiresToPlot(Gen.DemodulatorASK(ztASK, wiadomosc.Count, Fs, Ts, A1,2, "DemodulacjaAsk12"));
                    var otrzymanaWiadomoscASK = Gen.BinToString(Gen.DemodulatorASK(ztASK, wiadomosc.Count, Fs, Ts, A1));
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n[" + str + "]\nOrginalna wiadomość:\"" 
                        + wiadomoscString + "\"\n Otrzymana wiadomość: \""+ otrzymanaWiadomoscASK.ToString()+"\"";
                    //zmodulowana wiadomość.
                    chart1.Titles["Title1"].Text = "demodulacja ASK2";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    chart1.Titles["Title2"].Text = "t(s)";
                    Wykres.PlotChart();
                    break;
                case 2: //demodulatorASK1
                    A1 = 1;

                    //zmodulowana wiadomość. 
                    var ztFSK = Gen.ModFSK(wiadomosc, Fs, Ts, A1*100);

                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(ztFSK));
                    //Pierwszy etap demodulacji
                    Wykres.AddSeiresToPlot(Gen.DemodulatorFSK(ztFSK, wiadomosc.Count, Fs, Ts, A1 * 140,"DemodulacjaAsk1"));

                    var otrzymanaWiadomoscFSK = Gen.BinToString(Gen.DemodulatorFSK(ztFSK, wiadomosc.Count, Fs, Ts, A1));
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n["+str+"]\nOrginalna wiadomość:\"" 
                        + wiadomoscString + "\"\n Otrzymana wiadomość: \"" + otrzymanaWiadomoscFSK.ToString() + "\"";
                    //                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(zt));
                    chart1.Titles["Title1"].Text = "demodulacja FSK";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;
                case 3: //demodulatorASK1
                    A1 = 1;
                    Fs = 1500;
                    Ts = 2;
                    //zmodulowana wiadomość.
                    var ztPSK = Gen.ModPSK(wiadomosc, Fs, Ts, A1*100);

                    Wykres.AddSeiresToPlot(Gen.GenSeriesFromPoints(ztPSK));

                    Wykres.AddSeiresToPlot(Gen.DemodulatorPSK(ztPSK, wiadomosc.Count, Fs, Ts, A1*140, 1, "DemodulacjaPSK"));

                    Wykres.AddSeiresToPlot(Gen.DemodulatorPSK(ztPSK, wiadomosc.Count, Fs, Ts, A1, 2, "DemodulacjaPSK2"));

                    var otrzymanaWiadomoscPSK = Gen.BinToString(Gen.DemodulatorPSK(ztPSK, wiadomosc.Count, Fs, Ts, A1));
                    NazwaFunkcji = "Ts = " + Ts + " Fs = " + Fs + " A = " + A1 + "\n[" + str + "]\nOrginalna wiadomość:\"" 
                        + wiadomoscString + "\"\n Otrzymana wiadomość: \"" + otrzymanaWiadomoscPSK.ToString() + "\"";
                    chart1.Titles["Title1"].Text = "demodulacja PSK";
                    chart1.Titles["Title2"].Text = "t(s)";
                    chart1.Titles["Title3"].Text = NazwaFunkcji;
                    Wykres.PlotChart();
                    break;

            }
        }

        private void Laboratoria6()
        {
            double Ts = 2;//sec
            double Fs = 1500;//Hz
            double F = 1;//Hz
            string NazwaFunkcji;
            double A1 = 0;
            double A2 = 0;
            switch (NumberLevel2)
            {
                case 1: //demodulatorASK1

                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
        }

#endregion

        #region GUI

        private void buttonExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            foreach (var series in chart1.Series)
            {
                series.Points.Clear();
            }
        }

        private void buttonSavePlot_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Images|*.png";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
                chart1.SaveImage(saveFileDialog.FileName,ImageFormat.Png);
        }

        private void chart1_Enter(object sender, EventArgs e)
        {
            chart1.ChartAreas[0].AxisX.ScaleView.Zoomable = true;
            chart1.ChartAreas[0].AxisY.ScaleView.Zoomable = true;
            chart1.MouseWheel += new MouseEventHandler(chData_MouseWheel);
            //TODO działa string to Bin i Bin to str
//            var a = Gen.StringToBin("olek");
//            var b = Gen.BinToString(a);

            switch (NumberLevel1)
            {
                case 1:
                    Laboratoria1();
                    break;
                case 2:
                    Laboratoria2();
                    break;
                case 3:
                    Laboratoria3();
                    break;
                case 4:
                    Laboratoria4();
                    break;
                case 5:
                    Laboratoria5();
                    break;
                case 6:
                    Laboratoria4();
                    break;
                case 7:
                    Laboratoria4();
                    break;
                default:
                    break;
            }
            chart1.ChartAreas[0].RecalculateAxesScale();
        }

        private void ButtonPlot_Click(object sender, EventArgs e)
        {
            chart1_Enter(this, e);
        }

        private void chData_MouseWheel(object sender, MouseEventArgs e)
        {
            try
            {
                if (e.Delta < 0)
                {
                    chart1.ChartAreas[0].AxisX.ScaleView.ZoomReset();
                    chart1.ChartAreas[0].AxisY.ScaleView.ZoomReset();
                }

                if (e.Delta > 0)
                {
                    double xMin = chart1.ChartAreas[0].AxisX.ScaleView.ViewMinimum;
                    double xMax = chart1.ChartAreas[0].AxisX.ScaleView.ViewMaximum;
                    double yMin = chart1.ChartAreas[0].AxisY.ScaleView.ViewMinimum;
                    double yMax = chart1.ChartAreas[0].AxisY.ScaleView.ViewMaximum;

                    double posXStart = chart1.ChartAreas[0].AxisX.PixelPositionToValue(e.Location.X) - (xMax - xMin) / 2;
                    double posXFinish = chart1.ChartAreas[0].AxisX.PixelPositionToValue(e.Location.X) + (xMax - xMin) / 2;
                    double posYStart = chart1.ChartAreas[0].AxisY.PixelPositionToValue(e.Location.Y) - (yMax - yMin) / 2;
                    double posYFinish = chart1.ChartAreas[0].AxisY.PixelPositionToValue(e.Location.Y) + (yMax - yMin) / 2;

                    chart1.ChartAreas[0].AxisX.ScaleView.Zoom(posXStart, posXFinish);
                    chart1.ChartAreas[0].AxisY.ScaleView.Zoom(posYStart, posYFinish);
                }
            }
            catch { }
        }

        private void chart1_MouseEnter(object sender, EventArgs e)
        {
            this.chart1.Focus();
        }

        private void chart1_MouseLeave(object sender, EventArgs e)
        {
            this.chart1.Parent.Focus();
        }

        #region RadioButtons

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel1 = 1;
            radioButtonZadanie1.Text = "Sinusoida";
            radioButtonZadanie1.Enabled = true;
            radioButtonZadanie1.Checked = true;

            radioButtonZadanie2.Text = "w1<w2";
            radioButtonZadanie2.Enabled = true;

            radioButtonZadanie3.Text = "w1>w2";
            radioButtonZadanie3.Enabled = true;

            radioButtonZadanie4.Text = "w1=w2";
            radioButtonZadanie4.Enabled = true;

            radioButtonZadanie5.Text = "k=8";
            radioButtonZadanie5.Enabled = true;

            radioButtonZadanie6.Text = "k=16";
            radioButtonZadanie6.Enabled = true;

            radioButtonZadanie7.Text = "k=32";
            radioButtonZadanie7.Enabled = true;
        }
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel1 = 2;
            radioButtonZadanie1.Text = "Widmo Sinusoidy";
            radioButtonZadanie1.Enabled = true;
            radioButtonZadanie1.Checked = true;

            radioButtonZadanie2.Text = "Widmo w1<w2";
            radioButtonZadanie2.Enabled = true;

            radioButtonZadanie3.Text = "Widmo w1>w2";
            radioButtonZadanie3.Enabled = true;

            radioButtonZadanie4.Text = "Widmo w1=w2";
            radioButtonZadanie4.Enabled = true;

            radioButtonZadanie5.Text = "Widmo k=8";
            radioButtonZadanie5.Enabled = true;

            radioButtonZadanie6.Text = "Widmo k=16";
            radioButtonZadanie6.Enabled = true;

            radioButtonZadanie7.Text = "Widmo k=32";
            radioButtonZadanie7.Enabled = true;
        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel1 = 3;
            radioButtonZadanie1.Text = "W Mod AM 0.3";
            radioButtonZadanie1.Enabled = true;
            radioButtonZadanie1.Checked = true;

            radioButtonZadanie2.Text = "W Mod AM 0.9";
            radioButtonZadanie2.Enabled = true;

            radioButtonZadanie3.Text = "W Mod AM 13";
            radioButtonZadanie3.Enabled = true;

            radioButtonZadanie4.Text = "W Mod PM 0.5";
            radioButtonZadanie4.Enabled = true;

            radioButtonZadanie5.Text = "W Mod PM 1";
            radioButtonZadanie5.Enabled = true;

            radioButtonZadanie6.Text = "W Mod PM 22";
            radioButtonZadanie6.Enabled = true;

            radioButtonZadanie7.Text = "";
            radioButtonZadanie7.Enabled = false;
        }
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel1 = 4;
            radioButtonZadanie1.Text = "Mod ASK1";
            radioButtonZadanie1.Checked = true;
            radioButtonZadanie1.Enabled = true;
            radioButtonZadanie2.Text = "Mod ASK2";
            radioButtonZadanie2.Enabled = true;
            radioButtonZadanie3.Text = "Mod FSK";
            radioButtonZadanie3.Enabled = true;
            radioButtonZadanie4.Text = "Mod PSK";
            radioButtonZadanie4.Enabled = true;
            radioButtonZadanie5.Text = "Square Wave";
            radioButtonZadanie5.Enabled = true;
            radioButtonZadanie6.Text = "";
            radioButtonZadanie6.Enabled = false;
            radioButtonZadanie7.Text = "";
            radioButtonZadanie7.Enabled = false;
        }
        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel1 = 5;
            radioButtonZadanie1.Text = "Dmod ASK";
            radioButtonZadanie1.Checked = true;
            radioButtonZadanie2.Text = "Dmod FSK";
            radioButtonZadanie3.Text = "Dmod PSK";
            radioButtonZadanie4.Text = "";
            radioButtonZadanie4.Enabled = false;
            radioButtonZadanie5.Text = "";
            radioButtonZadanie5.Enabled = false;
            radioButtonZadanie6.Text = "";
            radioButtonZadanie6.Enabled = false;
            radioButtonZadanie7.Text = "";
            radioButtonZadanie7.Enabled = false;
        }
#endregion

        #region Czyste RadioButtony
        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void radioButton7_CheckedChanged(object sender, EventArgs e)
        {

        }
        #endregion

        #region RadioButtony Lvl2
        private void radioButtonZadanie1_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 1;
        }
        private void radioButtonZadanie2_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 2;
        }
        private void radioButtonZadanie3_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 3;
        }
        private void radioButtonZadanie4_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 4;
        }
        private void radioButtonZadanie5_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 5;
        }
        private void radioButtonZadanie6_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 6;
        }
        private void radioButtonZadanie7_CheckedChanged(object sender, EventArgs e)
        {
            NumberLevel2 = 7;
        }
        #endregion

        #endregion

    }
}
