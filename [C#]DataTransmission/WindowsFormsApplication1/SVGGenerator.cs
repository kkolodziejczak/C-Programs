using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{

    public static class SVGGenerator
    {
        private static List<string> SVGPicture;
        private static string StrokeColor;
        private static double StrokeWidth;
        private static string StrokeStyle;

        static SVGGenerator()
        {
            StrokeColor = "black";
            StrokeWidth = 1.0;
            StrokeStyle = "solid";
        }

        public static void SavePicture(List<Point> points)
        {
            SVGPicture = PrepareSVGPictureList();

            for (int i = 0; i < points.Count-1; i++)
                SVGPicture.Add(PrepareCircleString(points[i].x, points[i].y, 0.5,100));
//                SVGPicture.Add(PrepareLineString(points[i].x, points[i].y, points[i+1].x, points[i+1].y));

            SVGPicture.Add("</svg>");

            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Vector Images|*.svg";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
                File.WriteAllLines(saveFileDialog.FileName,SVGPicture);
        }

        private static List<string> PrepareSVGPictureList()
        {
            var list = new List<string>();
            list.Add("<svg width=\"640\" height=\"480\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">");
            return list;
        }

        private static string PrepareLineString(double x1, double y1, double x2, double y2)
        {
            var str = new StringBuilder();
                str.Append("<line ");
                str.Append("x1=\"" + x1 + "\" ");
                str.Append("y1=\"" + y1 + "\" ");
                str.Append("x2=\"" + x2 + "\" ");
                str.Append("y2=\"" + y2 + "\" ");
                str.Append("style=\"stroke:" + StrokeColor + ";" 
                                  + "stroke-width:" + StrokeWidth + ";" + "stroke-" + StrokeStyle + ":1,1\"/>");

            return str.ToString();
        }

        private static string PrepareCircleString(double cx, double cy, double r, double multiplayer)
        {
            var str = new StringBuilder();
            str.Append("<circle ");
            str.Append("cx=\"" + cx * multiplayer + "\" ");
            str.Append("cy=\"" + cy * multiplayer + "\" ");
            str.Append("r=\"" + r + "\"/>");

            return str.ToString();
        }

    }
}
