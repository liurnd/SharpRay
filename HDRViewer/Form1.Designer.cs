namespace HDRViewer
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.gammaValue = new System.Windows.Forms.TrackBar();
            this.button1 = new System.Windows.Forms.Button();
            this.ISOValue = new System.Windows.Forms.TrackBar();
            this.gammaText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.isoText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rgbHistogram1 = new HDRViewer.RGBHistogram();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gammaValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ISOValue)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(330, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(1032, 621);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // gammaValue
            // 
            this.gammaValue.Location = new System.Drawing.Point(6, 161);
            this.gammaValue.Maximum = 200;
            this.gammaValue.Minimum = 1;
            this.gammaValue.Name = "gammaValue";
            this.gammaValue.Size = new System.Drawing.Size(318, 45);
            this.gammaValue.TabIndex = 1;
            this.gammaValue.Value = 1;
            this.gammaValue.Scroll += new System.EventHandler(this.gammaValue_Scroll);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 20);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Open";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // ISOValue
            // 
            this.ISOValue.LargeChange = 2;
            this.ISOValue.Location = new System.Drawing.Point(6, 98);
            this.ISOValue.Maximum = 40;
            this.ISOValue.Minimum = 1;
            this.ISOValue.Name = "ISOValue";
            this.ISOValue.Size = new System.Drawing.Size(318, 45);
            this.ISOValue.TabIndex = 3;
            this.ISOValue.Value = 1;
            this.ISOValue.Scroll += new System.EventHandler(this.ISOValue_Scroll);
            // 
            // gammaText
            // 
            this.gammaText.Location = new System.Drawing.Point(224, 134);
            this.gammaText.Name = "gammaText";
            this.gammaText.Size = new System.Drawing.Size(100, 21);
            this.gammaText.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(183, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 6;
            this.label2.Text = "Gamma";
            // 
            // isoText
            // 
            this.isoText.Location = new System.Drawing.Point(224, 71);
            this.isoText.Name = "isoText";
            this.isoText.Size = new System.Drawing.Size(100, 21);
            this.isoText.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(195, 74);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "ISO";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rgbHistogram1);
            this.groupBox1.Controls.Add(this.gammaText);
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.isoText);
            this.groupBox1.Controls.Add(this.gammaValue);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.ISOValue);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Left;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(330, 621);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Operator";
            // 
            // rgbHistogram1
            // 
            this.rgbHistogram1.BackColor = System.Drawing.Color.DimGray;
            this.rgbHistogram1.Location = new System.Drawing.Point(6, 212);
            this.rgbHistogram1.Name = "rgbHistogram1";
            this.rgbHistogram1.Size = new System.Drawing.Size(318, 219);
            this.rgbHistogram1.TabIndex = 8;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1362, 621);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "HDR Viewer";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gammaValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ISOValue)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TrackBar gammaValue;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TrackBar ISOValue;
        private System.Windows.Forms.TextBox gammaText;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox isoText;
        private System.Windows.Forms.Label label1;
        private RGBHistogram rgbHistogram1;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}

