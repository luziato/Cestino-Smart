namespace ChatClient
{
    partial class Client
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
            this.components = new System.ComponentModel.Container();
            this.txtName = new System.Windows.Forms.TextBox();
            this.txtServerIP = new System.Windows.Forms.TextBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.rtxtConversation = new System.Windows.Forms.RichTextBox();
            this.txtMessage = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.module = new System.Windows.Forms.Label();
            this.angle = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.y = new System.Windows.Forms.Label();
            this.x = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.nudVel = new System.Windows.Forms.NumericUpDown();
            this.nudTempo = new System.Windows.Forms.NumericUpDown();
            this.btnDX = new System.Windows.Forms.Button();
            this.btnIndietro = new System.Windows.Forms.Button();
            this.btnAvanti = new System.Windows.Forms.Button();
            this.btnSX = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudVel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTempo)).BeginInit();
            this.SuspendLayout();
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(75, 27);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(150, 20);
            this.txtName.TabIndex = 1;
            this.txtName.Text = "COMMANDER";
            // 
            // txtServerIP
            // 
            this.txtServerIP.Location = new System.Drawing.Point(75, 53);
            this.txtServerIP.Name = "txtServerIP";
            this.txtServerIP.Size = new System.Drawing.Size(150, 20);
            this.txtServerIP.TabIndex = 3;
            this.txtServerIP.Text = "192.168.1.213";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(239, 27);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(92, 46);
            this.btnConnect.TabIndex = 4;
            this.btnConnect.Text = "&Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // rtxtConversation
            // 
            this.rtxtConversation.Location = new System.Drawing.Point(12, 109);
            this.rtxtConversation.Name = "rtxtConversation";
            this.rtxtConversation.ReadOnly = true;
            this.rtxtConversation.Size = new System.Drawing.Size(383, 168);
            this.rtxtConversation.TabIndex = 1;
            this.rtxtConversation.Text = "";
            // 
            // txtMessage
            // 
            this.txtMessage.Location = new System.Drawing.Point(8, 22);
            this.txtMessage.Multiline = true;
            this.txtMessage.Name = "txtMessage";
            this.txtMessage.Size = new System.Drawing.Size(329, 57);
            this.txtMessage.TabIndex = 0;
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(349, 22);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(86, 57);
            this.btnSend.TabIndex = 1;
            this.btnSend.Text = "&Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnDisconnect);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtName);
            this.groupBox1.Controls.Add(this.txtServerIP);
            this.groupBox1.Controls.Add(this.btnConnect);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(443, 91);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection Options";
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Location = new System.Drawing.Point(337, 27);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(92, 46);
            this.btnDisconnect.TabIndex = 5;
            this.btnDisconnect.Text = "&Disconnect";
            this.btnDisconnect.UseVisualStyleBackColor = true;
            this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Server IP:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "User Name:";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtMessage);
            this.groupBox2.Controls.Add(this.btnSend);
            this.groupBox2.Location = new System.Drawing.Point(6, 292);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(449, 90);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Message";
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(401, 109);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(54, 23);
            this.btnExit.TabIndex = 3;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(401, 254);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(54, 23);
            this.button1.TabIndex = 13;
            this.button1.Text = "Cl&ear";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.nudVel);
            this.groupBox3.Controls.Add(this.nudTempo);
            this.groupBox3.Controls.Add(this.btnDX);
            this.groupBox3.Controls.Add(this.btnIndietro);
            this.groupBox3.Controls.Add(this.btnAvanti);
            this.groupBox3.Controls.Add(this.btnSX);
            this.groupBox3.Location = new System.Drawing.Point(6, 388);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(449, 169);
            this.groupBox3.TabIndex = 14;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Controlli";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.module);
            this.groupBox4.Controls.Add(this.angle);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.y);
            this.groupBox4.Controls.Add(this.x);
            this.groupBox4.Controls.Add(this.label5);
            this.groupBox4.Location = new System.Drawing.Point(231, 84);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(200, 79);
            this.groupBox4.TabIndex = 22;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Joystick data:";
            // 
            // module
            // 
            this.module.AutoSize = true;
            this.module.Location = new System.Drawing.Point(134, 45);
            this.module.Name = "module";
            this.module.Size = new System.Drawing.Size(30, 13);
            this.module.TabIndex = 5;
            this.module.Text = "mod:";
            // 
            // angle
            // 
            this.angle.AutoSize = true;
            this.angle.Location = new System.Drawing.Point(71, 45);
            this.angle.Name = "angle";
            this.angle.Size = new System.Drawing.Size(28, 13);
            this.angle.TabIndex = 4;
            this.angle.Text = "ang:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 45);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(34, 13);
            this.label8.TabIndex = 3;
            this.label8.Text = "Polar:";
            // 
            // y
            // 
            this.y.AutoSize = true;
            this.y.Location = new System.Drawing.Point(134, 20);
            this.y.Name = "y";
            this.y.Size = new System.Drawing.Size(15, 13);
            this.y.TabIndex = 2;
            this.y.Text = "y:";
            // 
            // x
            // 
            this.x.AutoSize = true;
            this.x.Location = new System.Drawing.Point(71, 20);
            this.x.Name = "x";
            this.x.Size = new System.Drawing.Size(15, 13);
            this.x.TabIndex = 1;
            this.x.Text = "x:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(7, 20);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Cartesian:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(259, 60);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 13);
            this.label4.TabIndex = 20;
            this.label4.Text = "Velocità";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(241, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 19;
            this.label3.Text = "Tempo (mS)";
            // 
            // nudVel
            // 
            this.nudVel.Location = new System.Drawing.Point(311, 58);
            this.nudVel.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.nudVel.Name = "nudVel";
            this.nudVel.Size = new System.Drawing.Size(120, 20);
            this.nudVel.TabIndex = 18;
            this.nudVel.Value = new decimal(new int[] {
            127,
            0,
            0,
            0});
            // 
            // nudTempo
            // 
            this.nudTempo.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.nudTempo.Location = new System.Drawing.Point(311, 21);
            this.nudTempo.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nudTempo.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nudTempo.Name = "nudTempo";
            this.nudTempo.Size = new System.Drawing.Size(120, 20);
            this.nudTempo.TabIndex = 17;
            this.nudTempo.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // btnDX
            // 
            this.btnDX.Location = new System.Drawing.Point(149, 33);
            this.btnDX.Name = "btnDX";
            this.btnDX.Size = new System.Drawing.Size(60, 46);
            this.btnDX.TabIndex = 16;
            this.btnDX.Text = "DX";
            this.btnDX.UseVisualStyleBackColor = true;
            //this.btnDX.Click += new System.EventHandler(this.btnDX_Click_1);
            // 
            // btnIndietro
            // 
            this.btnIndietro.Location = new System.Drawing.Point(83, 64);
            this.btnIndietro.Name = "btnIndietro";
            this.btnIndietro.Size = new System.Drawing.Size(60, 46);
            this.btnIndietro.TabIndex = 15;
            this.btnIndietro.Text = "Indietro";
            this.btnIndietro.UseVisualStyleBackColor = true;
            // 
            // btnAvanti
            // 
            this.btnAvanti.Location = new System.Drawing.Point(83, 12);
            this.btnAvanti.Name = "btnAvanti";
            this.btnAvanti.Size = new System.Drawing.Size(60, 46);
            this.btnAvanti.TabIndex = 14;
            this.btnAvanti.Text = "Avanti";
            this.btnAvanti.UseVisualStyleBackColor = true;
            //this.btnAvanti.Click += new System.EventHandler(this.btnAvanti_Click);
            // 
            // btnSX
            // 
            this.btnSX.Location = new System.Drawing.Point(17, 33);
            this.btnSX.Name = "btnSX";
            this.btnSX.Size = new System.Drawing.Size(60, 46);
            this.btnSX.TabIndex = 13;
            this.btnSX.Text = "SX";
            this.btnSX.UseVisualStyleBackColor = true;
            // 
            // Client
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(467, 565);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.rtxtConversation);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Client";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "UDP Client (Robot side)";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Client_FormClosing);
            this.Load += new System.EventHandler(this.Client_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudVel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTempo)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.TextBox txtServerIP;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.RichTextBox rtxtConversation;
        private System.Windows.Forms.TextBox txtMessage;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown nudVel;
        private System.Windows.Forms.NumericUpDown nudTempo;
        private System.Windows.Forms.Button btnDX;
        private System.Windows.Forms.Button btnIndietro;
        private System.Windows.Forms.Button btnAvanti;
        private System.Windows.Forms.Button btnSX;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label module;
        private System.Windows.Forms.Label angle;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label y;
        private System.Windows.Forms.Label x;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Timer timer1;
    }
}

