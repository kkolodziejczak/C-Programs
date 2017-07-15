namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.Title title2 = new System.Windows.Forms.DataVisualization.Charting.Title();
            System.Windows.Forms.DataVisualization.Charting.Title title3 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.ButtonPlot = new System.Windows.Forms.Button();
            this.buttonSavePlot = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton5 = new System.Windows.Forms.RadioButton();
            this.radioButton6 = new System.Windows.Forms.RadioButton();
            this.radioButton7 = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButtonZadanie7 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie6 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie5 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie4 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie3 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie2 = new System.Windows.Forms.RadioButton();
            this.radioButtonZadanie1 = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // chart1
            // 
            chartArea1.AxisX.LabelStyle.Format = "{0:0}";
            chartArea1.AxisX.LabelStyle.Interval = 100D;
            chartArea1.AxisX.LabelStyle.IntervalOffset = 0D;
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Location = new System.Drawing.Point(12, 12);
            this.chart1.Name = "chart1";
            this.chart1.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.Bright;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.IsVisibleInLegend = false;
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(705, 328);
            this.chart1.TabIndex = 0;
            this.chart1.Text = "chart1";
            title1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Bold);
            title1.Name = "Title1";
            title1.Text = "Test Title";
            title2.Docking = System.Windows.Forms.DataVisualization.Charting.Docking.Bottom;
            title2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F);
            title2.Name = "Title2";
            title2.Text = "t[s]";
            title3.Name = "Title3";
            title3.Text = "23";
            this.chart1.Titles.Add(title1);
            this.chart1.Titles.Add(title2);
            this.chart1.Titles.Add(title3);
            this.chart1.Enter += new System.EventHandler(this.chart1_Enter);
            this.chart1.MouseEnter += new System.EventHandler(this.chart1_MouseEnter);
            this.chart1.MouseLeave += new System.EventHandler(this.chart1_MouseLeave);
            // 
            // ButtonPlot
            // 
            this.ButtonPlot.Location = new System.Drawing.Point(723, 204);
            this.ButtonPlot.Name = "ButtonPlot";
            this.ButtonPlot.Size = new System.Drawing.Size(75, 23);
            this.ButtonPlot.TabIndex = 1;
            this.ButtonPlot.Text = "Plot";
            this.ButtonPlot.UseVisualStyleBackColor = true;
            this.ButtonPlot.Click += new System.EventHandler(this.ButtonPlot_Click);
            // 
            // buttonSavePlot
            // 
            this.buttonSavePlot.Location = new System.Drawing.Point(723, 233);
            this.buttonSavePlot.Name = "buttonSavePlot";
            this.buttonSavePlot.Size = new System.Drawing.Size(75, 23);
            this.buttonSavePlot.TabIndex = 2;
            this.buttonSavePlot.Text = "Save PNG";
            this.buttonSavePlot.UseVisualStyleBackColor = true;
            this.buttonSavePlot.Click += new System.EventHandler(this.buttonSavePlot_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(723, 262);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(75, 23);
            this.buttonClear.TabIndex = 3;
            this.buttonClear.Text = "Clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(723, 291);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 4;
            this.buttonExit.Text = "Exit";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(6, 19);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(49, 17);
            this.radioButton1.TabIndex = 5;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Lab1";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(6, 42);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(49, 17);
            this.radioButton2.TabIndex = 6;
            this.radioButton2.Text = "Lab2";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(6, 65);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(49, 17);
            this.radioButton3.TabIndex = 7;
            this.radioButton3.Text = "Lab3";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton3_CheckedChanged);
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(6, 88);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(49, 17);
            this.radioButton4.TabIndex = 8;
            this.radioButton4.Text = "Lab4";
            this.radioButton4.UseVisualStyleBackColor = true;
            this.radioButton4.CheckedChanged += new System.EventHandler(this.radioButton4_CheckedChanged);
            // 
            // radioButton5
            // 
            this.radioButton5.AutoSize = true;
            this.radioButton5.Location = new System.Drawing.Point(6, 111);
            this.radioButton5.Name = "radioButton5";
            this.radioButton5.Size = new System.Drawing.Size(49, 17);
            this.radioButton5.TabIndex = 9;
            this.radioButton5.TabStop = true;
            this.radioButton5.Text = "Lab5";
            this.radioButton5.UseVisualStyleBackColor = true;
            this.radioButton5.CheckedChanged += new System.EventHandler(this.radioButton5_CheckedChanged);
            // 
            // radioButton6
            // 
            this.radioButton6.AutoSize = true;
            this.radioButton6.Enabled = false;
            this.radioButton6.Location = new System.Drawing.Point(6, 134);
            this.radioButton6.Name = "radioButton6";
            this.radioButton6.Size = new System.Drawing.Size(49, 17);
            this.radioButton6.TabIndex = 10;
            this.radioButton6.TabStop = true;
            this.radioButton6.Text = "Lab6";
            this.radioButton6.UseVisualStyleBackColor = true;
            this.radioButton6.CheckedChanged += new System.EventHandler(this.radioButton6_CheckedChanged);
            // 
            // radioButton7
            // 
            this.radioButton7.AutoSize = true;
            this.radioButton7.Enabled = false;
            this.radioButton7.Location = new System.Drawing.Point(6, 157);
            this.radioButton7.Name = "radioButton7";
            this.radioButton7.Size = new System.Drawing.Size(49, 17);
            this.radioButton7.TabIndex = 11;
            this.radioButton7.TabStop = true;
            this.radioButton7.Text = "Lab7";
            this.radioButton7.UseVisualStyleBackColor = true;
            this.radioButton7.CheckedChanged += new System.EventHandler(this.radioButton7_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Controls.Add(this.radioButton2);
            this.groupBox1.Controls.Add(this.radioButton7);
            this.groupBox1.Controls.Add(this.radioButton3);
            this.groupBox1.Controls.Add(this.radioButton6);
            this.groupBox1.Controls.Add(this.radioButton4);
            this.groupBox1.Controls.Add(this.radioButton5);
            this.groupBox1.Location = new System.Drawing.Point(723, 14);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(78, 184);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Laboratoria";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioButtonZadanie7);
            this.groupBox2.Controls.Add(this.radioButtonZadanie6);
            this.groupBox2.Controls.Add(this.radioButtonZadanie5);
            this.groupBox2.Controls.Add(this.radioButtonZadanie4);
            this.groupBox2.Controls.Add(this.radioButtonZadanie3);
            this.groupBox2.Controls.Add(this.radioButtonZadanie2);
            this.groupBox2.Controls.Add(this.radioButtonZadanie1);
            this.groupBox2.Location = new System.Drawing.Point(807, 14);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(113, 300);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Zadanie";
            // 
            // radioButtonZadanie7
            // 
            this.radioButtonZadanie7.AutoSize = true;
            this.radioButtonZadanie7.Location = new System.Drawing.Point(6, 157);
            this.radioButtonZadanie7.Name = "radioButtonZadanie7";
            this.radioButtonZadanie7.Size = new System.Drawing.Size(49, 17);
            this.radioButtonZadanie7.TabIndex = 6;
            this.radioButtonZadanie7.TabStop = true;
            this.radioButtonZadanie7.Text = "k=32";
            this.radioButtonZadanie7.UseVisualStyleBackColor = true;
            this.radioButtonZadanie7.CheckedChanged += new System.EventHandler(this.radioButtonZadanie7_CheckedChanged);
            // 
            // radioButtonZadanie6
            // 
            this.radioButtonZadanie6.AutoSize = true;
            this.radioButtonZadanie6.Location = new System.Drawing.Point(6, 134);
            this.radioButtonZadanie6.Name = "radioButtonZadanie6";
            this.radioButtonZadanie6.Size = new System.Drawing.Size(49, 17);
            this.radioButtonZadanie6.TabIndex = 5;
            this.radioButtonZadanie6.TabStop = true;
            this.radioButtonZadanie6.Text = "k=16";
            this.radioButtonZadanie6.UseVisualStyleBackColor = true;
            this.radioButtonZadanie6.CheckedChanged += new System.EventHandler(this.radioButtonZadanie6_CheckedChanged);
            // 
            // radioButtonZadanie5
            // 
            this.radioButtonZadanie5.AutoSize = true;
            this.radioButtonZadanie5.Location = new System.Drawing.Point(6, 111);
            this.radioButtonZadanie5.Name = "radioButtonZadanie5";
            this.radioButtonZadanie5.Size = new System.Drawing.Size(43, 17);
            this.radioButtonZadanie5.TabIndex = 4;
            this.radioButtonZadanie5.TabStop = true;
            this.radioButtonZadanie5.Text = "k=8";
            this.radioButtonZadanie5.UseVisualStyleBackColor = true;
            this.radioButtonZadanie5.CheckedChanged += new System.EventHandler(this.radioButtonZadanie5_CheckedChanged);
            // 
            // radioButtonZadanie4
            // 
            this.radioButtonZadanie4.AutoSize = true;
            this.radioButtonZadanie4.Location = new System.Drawing.Point(6, 88);
            this.radioButtonZadanie4.Name = "radioButtonZadanie4";
            this.radioButtonZadanie4.Size = new System.Drawing.Size(59, 17);
            this.radioButtonZadanie4.TabIndex = 3;
            this.radioButtonZadanie4.TabStop = true;
            this.radioButtonZadanie4.Text = "w1=w2";
            this.radioButtonZadanie4.UseVisualStyleBackColor = true;
            this.radioButtonZadanie4.CheckedChanged += new System.EventHandler(this.radioButtonZadanie4_CheckedChanged);
            // 
            // radioButtonZadanie3
            // 
            this.radioButtonZadanie3.AutoSize = true;
            this.radioButtonZadanie3.Location = new System.Drawing.Point(6, 65);
            this.radioButtonZadanie3.Name = "radioButtonZadanie3";
            this.radioButtonZadanie3.Size = new System.Drawing.Size(59, 17);
            this.radioButtonZadanie3.TabIndex = 2;
            this.radioButtonZadanie3.TabStop = true;
            this.radioButtonZadanie3.Text = "w1>w2";
            this.radioButtonZadanie3.UseVisualStyleBackColor = true;
            this.radioButtonZadanie3.CheckedChanged += new System.EventHandler(this.radioButtonZadanie3_CheckedChanged);
            // 
            // radioButtonZadanie2
            // 
            this.radioButtonZadanie2.AutoSize = true;
            this.radioButtonZadanie2.Location = new System.Drawing.Point(6, 42);
            this.radioButtonZadanie2.Name = "radioButtonZadanie2";
            this.radioButtonZadanie2.Size = new System.Drawing.Size(59, 17);
            this.radioButtonZadanie2.TabIndex = 1;
            this.radioButtonZadanie2.TabStop = true;
            this.radioButtonZadanie2.Text = "w1<w2";
            this.radioButtonZadanie2.UseVisualStyleBackColor = true;
            this.radioButtonZadanie2.CheckedChanged += new System.EventHandler(this.radioButtonZadanie2_CheckedChanged);
            // 
            // radioButtonZadanie1
            // 
            this.radioButtonZadanie1.AutoSize = true;
            this.radioButtonZadanie1.Location = new System.Drawing.Point(6, 19);
            this.radioButtonZadanie1.Name = "radioButtonZadanie1";
            this.radioButtonZadanie1.Size = new System.Drawing.Size(71, 17);
            this.radioButtonZadanie1.TabIndex = 0;
            this.radioButtonZadanie1.TabStop = true;
            this.radioButtonZadanie1.Text = "Sinusoida";
            this.radioButtonZadanie1.UseVisualStyleBackColor = true;
            this.radioButtonZadanie1.CheckedChanged += new System.EventHandler(this.radioButtonZadanie1_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(930, 354);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.buttonSavePlot);
            this.Controls.Add(this.ButtonPlot);
            this.Controls.Add(this.chart1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Button ButtonPlot;
        private System.Windows.Forms.Button buttonSavePlot;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.RadioButton radioButton5;
        private System.Windows.Forms.RadioButton radioButton6;
        private System.Windows.Forms.RadioButton radioButton7;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton radioButtonZadanie7;
        private System.Windows.Forms.RadioButton radioButtonZadanie6;
        private System.Windows.Forms.RadioButton radioButtonZadanie5;
        private System.Windows.Forms.RadioButton radioButtonZadanie4;
        private System.Windows.Forms.RadioButton radioButtonZadanie3;
        private System.Windows.Forms.RadioButton radioButtonZadanie2;
        private System.Windows.Forms.RadioButton radioButtonZadanie1;
    }
}

