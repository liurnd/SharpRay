using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HDRViewer
{
    public partial class RGBHistogram : UserControl
    {
        float DeltaX, DeltaY;
        public int offset;
        long[] numR, numG, numB, numGray;
        long maxNum;
        int xBaseOffset,barHeight,barY,xEndOffset;
        bool isPainting;
        RGBGLine[] lineList;
        public RGBHistogram()
        {
            isPainting = false;
            barHeight = 5;
            InitializeComponent();
        }

        public Bitmap targetBitmap
        {
            set { refreshHistogram(value); }
        }

        private void refreshHistogram(Bitmap b)
        {
            if (b == null)
                return;
            maxNum = 0;
            numR = new long[256];
            numG = new long[256];
            numB = new long[256];
            numGray = new long[256];
            lineList = new RGBGLine[256];

            for(int i = 0; i< b.Width;i++)
            {
                for(int j = 0; j<b.Height;j++)
                {
                    var c = b.GetPixel(i,j);
                    numR[c.R]++;
                    numG[c.G]++;
                    numB[c.B]++;
                    numGray[(byte)(c.GetBrightness() * 255)]++;
                    
                }
            }
            for (int i = 0; i<=255; i++)
            {
                lineList[i] = new RGBGLine(numR[i], numG[i], numB[i], numGray[i]);
                maxNum = Math.Max(Math.Max(Math.Max(Math.Max(numR[i], maxNum), numG[i]), numB[i]), numGray[i]);
            }

            calDeltas();
            isPainting = true;
            Refresh();
        }

        private void calDeltas()
        {
            DeltaX = (float)(this.Width - 2 * offset) / 255;
            DeltaY = (float)(this.Height - 2 * offset - barHeight) / maxNum;
            xBaseOffset = (Width - (255 * (int)DeltaX)) / 2;
            barY = Height - offset - barHeight / 2;
            xEndOffset = xBaseOffset + 256 * (int)DeltaX;
        }
        private void RGBHistogram_Resize(object sender, EventArgs e)
        {
            calDeltas();
        }

        private void RGBHistogram_Paint(object sender, PaintEventArgs e)
        {
            if (!isPainting)
                return;
            Graphics g = e.Graphics;
            int offsetX = xBaseOffset;
            for (int i = 0; i<= 255;i++)
            {
                lineList[i].drawLine(g, offsetX,Height-offset-barHeight,DeltaY);
                offsetX += (int)DeltaX;
            }

            var barPen = new Pen(Color.Black);
            g.DrawLine(barPen, xBaseOffset, barY, xEndOffset, barY);
            g.DrawLine(barPen, xBaseOffset, barY, xBaseOffset, barY + barHeight);
            g.DrawLine(barPen, xEndOffset, barY, xEndOffset, barY + barHeight);
        }
    }

    class RGBGLine
    {
        long[] nC;
        Color[] c;
        public RGBGLine(long R, long G, long B, long Gray)
        {
            nC = new long[4];
            c = new Color[4];
            nC[3] = Gray; c[3] = Color.Gray;
            /*if (R > G)
            {
                if (G > B)//R>G>B
                {
                    nC[0] = R; c[0] = Color.Red;
                    nC[1] = G; c[1] = Color.Green;
                    nC[2] = B; c[2] = Color.Blue;
                }
                else if (R > B)//R>B>G
                {
                    nC[0] = R; c[0] = Color.Red;
                    nC[1] = B; c[1] = Color.Blue;
                    nC[2] = G; c[2] = Color.Green;
                }
                else //B>R>G
                {
                    nC[0] = B; c[0] = Color.Blue;
                    nC[1] = R; c[1] = Color.Red;
                    nC[2] = G; c[2] = Color.Green;
                }
            }
            else
            {
                if (R > B)//G>R>B
                {
                    nC[0] = G; c[0] = Color.Green;
                    nC[1] = R; c[1] = Color.Red;
                    nC[2] = B; c[2] = Color.Blue;
                }
                else if (G > B)//G>B>R
                {
                    nC[0] = G; c[0] = Color.Green;
                    nC[1] = B; c[1] = Color.Blue;
                    nC[2] = R; c[2] = Color.Red;
                }
                else //B>G>R
                {*/
                    nC[0] = B; c[0] = Color.Blue;
                    nC[1] = G; c[1] = Color.Green;
                    nC[2] = R; c[2] = Color.Red;/*
                }
            }*/
        }
        public void drawLine(Graphics g,float offsetX, float offsetY, float dY)
        {
            var poBase = new PointF(offsetX, offsetY);
            var poUp = new PointF();
            poUp.X = offsetX;
            for (int i = 0 ; i< 4;i++)
            {
                poUp.Y = offsetY - dY * nC[i];
                g.DrawLine(new Pen(c[i]), poBase, poUp);
            }
        }
    }
}
