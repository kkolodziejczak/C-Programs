using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.DataVisualization.Charting;

namespace WindowsFormsApplication1
{
    class Plot
    {
        private List<Series> Seires = new List<Series>();
        private List<Series> SeiresToPlot = new List<Series>();
        private Chart Chart;

        public Plot()
        {
            throw new NotImplementedException();
        }

        public Plot(Chart _chart)
        {
            Chart = _chart;
        }

        public void PlotChart()
        {
            Chart.Series.Clear();
            foreach (var series in SeiresToPlot)
            {
                Chart.Series.Add(series);
            }
        }

        public void AddSeries(Series _series)
        {
            Seires.Add(_series);
        }

        public void AddSeiresToPlot(Series _series)
        {
            SeiresToPlot.Add(_series);
        }

    }
}
