using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using componentXtra;

namespace XYSimple
{
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class Form1 : System.Windows.Forms.Form
    {
        private componentXtra.XYGraph xyGraph1;
        private System.IO.Ports.SerialPort MonPortSerie;
        private List<int> list1 = new List<int>();
        private List<int> list2 = new List<int>();
        private int flag = new int();
        private Label label1;
        private Button button1;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private Label label2;
        private Label label3;
        private Label label4;
        private Button button2;
        private Button button3;
        private Button button4;
        private TextBox textBox4;
        private Label label5;
        private TextBox textBox5;
        private Label label6;
        private Label label7;
        private Label label8;
        private CheckBox checkBox1;
        private IContainer components;
        private delegate void _UseSerialPort(byte[] donnee);

        public Form1()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
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
            this.components = new System.ComponentModel.Container();
            this.xyGraph1 = new componentXtra.XYGraph();
            this.MonPortSerie = new System.IO.Ports.SerialPort(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // xyGraph1
            // 
            this.xyGraph1.BackColor = System.Drawing.Color.White;
            this.xyGraph1.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.xyGraph1.Location = new System.Drawing.Point(-1, 131);
            this.xyGraph1.Name = "xyGraph1";
            this.xyGraph1.Size = new System.Drawing.Size(720, 369);
            this.xyGraph1.TabIndex = 0;
            this.xyGraph1.XtraAutoScale = true;
            this.xyGraph1.XtraClassicLabels = true;
            this.xyGraph1.XtraFrame = false;
            this.xyGraph1.XtraLabelX = "N";
            this.xyGraph1.XtraLabelY = "mm";
            this.xyGraph1.XtraLogX = false;
            this.xyGraph1.XtraLogY = false;
            this.xyGraph1.XtraMinLeftMargin = 0;
            this.xyGraph1.XtraSelectPoint = false;
            this.xyGraph1.XtraShowGrid = true;
            this.xyGraph1.XtraShowLegend = true;
            this.xyGraph1.XtraTitle = "Distance";
            this.xyGraph1.XtraUpdateCursor = true;
            this.xyGraph1.XtraXdigits = 0;
            this.xyGraph1.XtraXmax = 100F;
            this.xyGraph1.XtraXmin = 0F;
            this.xyGraph1.XtraXstep = 0F;
            this.xyGraph1.XtraYdigits = 0;
            this.xyGraph1.XtraYmax = 440F;
            this.xyGraph1.XtraYmin = -50F;
            this.xyGraph1.XtraYstep = 0F;
            this.xyGraph1.Load += new System.EventHandler(this.xyGraph1_Load);
            this.xyGraph1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.xyGraph1_MouseClick);
            // 
            // MonPortSerie
            // 
            this.MonPortSerie.BaudRate = 19200;
            this.MonPortSerie.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.MonPortSerie_DataReceived);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(142, 102);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Distance :";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(22, 16);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Start COM";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(409, 15);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 3;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(409, 55);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 20);
            this.textBox2.TabIndex = 4;
            this.textBox2.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(409, 91);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 20);
            this.textBox3.TabIndex = 5;
            this.textBox3.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(383, 18);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(20, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Kp";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(383, 57);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(16, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Ki";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(383, 94);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(20, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Kd";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(22, 52);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 9;
            this.button2.Text = "Stop COM";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(22, 97);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 10;
            this.button3.Text = "Save *.csv";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(545, 62);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(110, 43);
            this.button4.TabIndex = 11;
            this.button4.Text = "Change Values";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(200, 19);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(29, 20);
            this.textBox4.TabIndex = 12;
            this.textBox4.TextChanged += new System.EventHandler(this.textBox4_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(142, 22);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(52, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Setpoint :";
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(200, 55);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(41, 20);
            this.textBox5.TabIndex = 14;
            this.textBox5.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(167, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(22, 13);
            this.label6.TabIndex = 15;
            this.label6.Text = "dt :";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(235, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(23, 13);
            this.label7.TabIndex = 16;
            this.label7.Text = "mm";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(247, 58);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 13);
            this.label8.TabIndex = 17;
            this.label8.Text = "mm";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(250, 101);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(85, 17);
            this.checkBox1.TabIndex = 18;
            this.checkBox1.Text = "Graph PWM";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(720, 502);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.xyGraph1);
            this.Name = "Form1";
            this.Text = "Beam & Ball v2.0";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.Run(new Form1());
        }

        private void xyGraph1_Load(object sender, System.EventArgs e)
        {
            xyGraph1.ClearGraph(0);
            xyGraph1.AddGraph("XtraTitle", DashStyle.Solid, Color.Red, 1, false);
            for (int i = 0; i < list1.Count; i++)
                xyGraph1.AddValue(0, (float)i, (float)list1[i]);
            xyGraph1.DrawAll();
        }

        private void xyGraph1_Load()
        {
            //xyGraph1.ClearGraph(0);
           // xyGraph1.AddGraph("Distance", DashStyle.Solid, Color.Red, 1, false);

            if (checkBox1.Checked)
            {
                xyGraph1.ClearGraph(0);
                xyGraph1.AddGraph("PWM", DashStyle.DashDot, Color.Blue, 1, false);
                if (list2.Count >= 1000)
                {
                    for (int i = list2.Count - 1000; i < list2.Count; i++)
                        xyGraph1.AddValue(0, (float)i, list2[i]);
                    xyGraph1.DrawAll();
                }
                else
                {
                    for (int i = 0; i < list2.Count; i++)
                        xyGraph1.AddValue(0, (float)i, list2[i]);
                    xyGraph1.DrawAll();
                }
            }

            else  {
                xyGraph1.ClearGraph(0);
                xyGraph1.AddGraph("Distance", DashStyle.Solid, Color.Red, 1, false);
               
                if (list1.Count >= 1000)
                {
                    for (int j = list1.Count - 1000; j < list1.Count; j++)
                        xyGraph1.AddValue(0, (float)j, list1[j]);
                    xyGraph1.DrawAll();
                }
                else
                {
                    for (int j = 0; j < list1.Count; j++)
                        xyGraph1.AddValue(0, (float)j, list1[j]);
                    xyGraph1.DrawAll();
                }
            }



        }

        private void UseSerialPort(byte[] donnee)
        {
            int x = 0;
            string toto = null;
            string s = System.Text.Encoding.ASCII.GetString(donnee);

            if (s[0] == 'P')
            {
                x = donnee[1];
                list1.Add(x);
                toto = System.Convert.ToString(x);              //actual_position
                label1.Text = "distance : " + toto + "mm";
            }
            if (s[0] == 'Q')
            {
                x = donnee[1] + 255;
                list1.Add(x);
                toto = System.Convert.ToString(x);        //actual_position
                label1.Text = "distance : " + toto + "mm"; ;
            }
            if (s[0] == 'W')
            {
                x = donnee[1];
                list2.Add(x);
                toto = System.Convert.ToString(x);        //PWM
                
            }

        }

        private void MonPortSerie_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int nb_octet = MonPortSerie.BytesToRead;
            byte[] trame = new byte[nb_octet];
            MonPortSerie.Read(trame, 0, nb_octet);

            if (this.InvokeRequired)
            {
                try
                {
                    this.Invoke(new _UseSerialPort(UseSerialPort), trame);
                }
                catch (Exception xcep)
                {
                    //MessageBox.Show(xcep.ToString());
                    return;
                }
            }
            xyGraph1_Load();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            string MonCOM = "COM1";
            try
            {
                MonPortSerie.PortName = MonCOM;
                MonPortSerie.Open();

                MonPortSerie.Write("F");
                MonPortSerie.Write("1");
                MonPortSerie.Write("\x0A");

            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                return;
            }
            //MessageBox.Show("Port série ouvert !");
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                MonPortSerie.Write("F");
                MonPortSerie.Write("0");
                MonPortSerie.Write("\x0A");
                MonPortSerie.Close();
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.ToString());
                return;
            }
            //MessageBox.Show("Port série fermé !");
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
                      

        }

        private void Form1_Load(object sender, EventArgs e)
        {
          

        }



        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                StreamWriter writer = new StreamWriter("Output_" + DateTime.Now.ToString("dd-MM-yyyy_HH-mm") + ".csv");
                for (int i = 0; i < list1.Count; i++)
                    writer.WriteLine(list1[i]+"."+list2[i]);
                writer.Close();
            }
            catch (Exception ece)
            {
                //MessageBox.Show(ece.ToString());
                return;
            }

        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length != 0)                  ////////Kp
            {
                try
                {
                    MonPortSerie.Write("K");
                    float buff = float.Parse(textBox1.Text);
                    string buff2 = buff.ToString();
                    MonPortSerie.Write(buff2);
                    MonPortSerie.Write("\x0A");
                    System.Threading.Thread.Sleep(5); 
             

                }

                catch (FormatException ex7)
                {
                    textBox1.Text = "no FLOAT";
                    return;
                }

                catch (Exception ex)
                {
                    //MessageBox.Show(ex.ToString());

                    return;
                }
            }
            if (textBox2.Text.Length != 0)                  ////////Ki
            {
                try
                {
                    MonPortSerie.Open();
                    MonPortSerie.Write("L");
                    float bufff = float.Parse(textBox2.Text);
                    string bufff2 = bufff.ToString();
                    MonPortSerie.Write(bufff2);
                    MonPortSerie.Write("\x0A");
                    System.Threading.Thread.Sleep(5);
                }
                catch (FormatException ex8)
                {
                    textBox2.Text = "no FLOAT";
                    return;
                }
                catch (Exception ex1)
                {
                    //MessageBox.Show(ex1.ToString());
                    return;
                }
            }
            if (textBox3.Text.Length != 0)                  ////////Kd
            {
                try
                {
                    MonPortSerie.Write("M");
                    float buffff = float.Parse(textBox3.Text);
                    string buffff2 = buffff.ToString();
                    MonPortSerie.Write(buffff2);
                    MonPortSerie.Write("\x0A");
                    System.Threading.Thread.Sleep(5);
                }
                catch (FormatException ex9)
                {
                    textBox3.Text = "no FLOAT";
                    return;
                }
                catch (Exception ex2)
                {
                    //MessageBox.Show(ex2.ToString());
                    return;
                }
            }

            if (textBox4.Text.Length != 0)          ////setpoint
            {
                try
                {
                    MonPortSerie.Write("S");
                    float bufffff = float.Parse(textBox4.Text);
                    string bufffff2 = bufffff.ToString();
                    MonPortSerie.Write(bufffff2);
                    MonPortSerie.Write("\x0A");
                    System.Threading.Thread.Sleep(5);
                }
                catch (FormatException ex10)
                {
                    textBox4.Text = "no FLOAT";
                    return;
                }
                catch (Exception ex3)
                {
                    //MessageBox.Show(ex3.ToString());
                    return;
                }
            }

            if (textBox5.Text.Length != 0)          ////dt
            {
                try
                {
                    MonPortSerie.Write("D");
                    int bufffff = int.Parse(textBox5.Text);
                    string bufffff2 = bufffff.ToString();
                    MonPortSerie.Write(bufffff2);
                    MonPortSerie.Write("\x0A");
                    System.Threading.Thread.Sleep(5);
                }
                catch (FormatException ex7)
                {
                    textBox5.Text = "no INT";
                    return;
                }
                catch (Exception ex4)
                {
                    //MessageBox.Show(ex2.ToString());                 
                    return;
                }
            }


        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {


        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void xyGraph1_MouseClick(object sender, MouseEventArgs e)
        {
          
            
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            flag%=2;
            flag++;
            xyGraph1.DrawAll();
            if (flag==0)
            {
                xyGraph1.ClearGraph(0);
            }
            else
            {
                xyGraph1.ClearGraph(1);
            }
           
        }
    }
}
