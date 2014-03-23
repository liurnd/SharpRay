using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace HDRViewer
{
    public partial class Form1 : Form
    {
        Bitmap canvas;
        int numPixel;
        HDRPixel[] HDRMap;
        int maxISO;float isoLogBase, standardISO;
        Timer refreshTimer;
        public Form1()
        {
            InitializeComponent();
            maxISO = 12800;
            isoLogBase = 1.2f;
            standardISO =maxISO / (float)Math.Pow(isoLogBase, ISOValue.Maximum);
            refreshTimer = new Timer();
            refreshTimer.Tick += timer_Tick;
            refreshTimer.Interval = 500;
        }

        private int  ISOtoLevel(float iso)
        {
            return (int)(Math.Log(iso / standardISO, isoLogBase));
        }

        private float LevelToISO(int level)
        {
            return standardISO * (float)Math.Pow(isoLogBase, level);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var of = new OpenFileDialog();
            if (of.ShowDialog() == System.Windows.Forms.DialogResult.Cancel)
                return;
            var result = of.FileName;
            readHDRFile(result);
            gammaValue.Value = 100;
            ISOValue.Value = ISOtoLevel(200);
            RefreshPicture();
        }

        private void readHDRFile(string fName)
        {
            var fIn = new System.IO.FileStream(fName, System.IO.FileMode.Open);
            System.IO.BinaryReader r = new System.IO.BinaryReader(fIn);

            //Read HDR Header
            var byteBuffer = r.ReadBytes(Marshal.SizeOf(typeof(HDRHeader)));
            var gchdrPtr = GCHandle.Alloc(byteBuffer, GCHandleType.Pinned);
            var hdrPtr = gchdrPtr.AddrOfPinnedObject();
            HDRHeader hdr = (HDRHeader)Marshal.PtrToStructure(hdrPtr, typeof(HDRHeader));
            gchdrPtr.Free();

            //Alloc HDRMap
            int i;
            numPixel = hdr.height * hdr.width;
            HDRMap = new HDRPixel[numPixel];

            //Read HDR Pixels
            byteBuffer = r.ReadBytes(numPixel * Marshal.SizeOf(typeof(HDRPixel)));
            var gcPixelListPtr = GCHandle.Alloc(byteBuffer, GCHandleType.Pinned);
            var pixelListPtr = gcPixelListPtr.AddrOfPinnedObject();
            for (i = 0; i < numPixel; i++)
            {
                int offset = i * Marshal.SizeOf(typeof(HDRPixel));
                HDRMap[i] = (HDRPixel)Marshal.PtrToStructure(pixelListPtr+offset, typeof(HDRPixel));
            }
            canvas = new Bitmap(hdr.width, hdr.height);
        }

        private void showCanvas(float ISO, float gamma)
        {
            isoText.Text = ISO.ToString();
            gammaText.Text = gamma.ToString();
            rgbHistogram1.offset = 10;
            rgbHistogram1.targetBitmap = canvas;
            pictureBox1.Image = canvas;
            pictureBox1.Refresh();
        }
        
        private void RefreshPicture()
        {
            refreshTimer.Stop();
            refreshTimer.Start();
        }
        private void timer_Tick(object sender,EventArgs e)
        {
            doRefreshPicture();
        }
        private void doRefreshPicture()
        {
            float gamma = gammaValue.Value / 100.0f;
            float ISO = LevelToISO(ISOValue.Value);

            int i;
            for (i = 0; i < numPixel; i++)
            {
                Color c = HDRMap[i].getColor(gamma, ISO);
                canvas.SetPixel(HDRMap[i].x, HDRMap[i].y, c);
            }
            showCanvas(ISO,gamma);
            refreshTimer.Stop();
        }

        private void ISOValue_Scroll(object sender, EventArgs e)
        {
            RefreshPicture();
        }

        private void gammaValue_Scroll(object sender, EventArgs e)
        {
            RefreshPicture();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct HDRHeader{
	    public int width, height;
    };
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct HDRPixel{
	    public int x, y;
	    public float r, g, b;
        public Color getColor(float gamma, float ISO)
        {
            byte tmpR, tmpG, tmpB;
            float Rr, Rb, Rg;
            Rr = (float)Math.Pow((r * ISO),gamma)*255;
            Rb = (float)Math.Pow((b * ISO), gamma)*255;
            Rg = (float)Math.Pow((g * ISO), gamma)*255;
            tmpR = Rr > 255 ? (byte)255 : (byte)Rr;
            tmpG = Rg > 255 ? (byte)255 : (byte)Rg;
            tmpB = Rb > 255 ? (byte)255 : (byte)Rb;
            return Color.FromArgb(tmpR, tmpG, tmpB);
        }
	};

}
