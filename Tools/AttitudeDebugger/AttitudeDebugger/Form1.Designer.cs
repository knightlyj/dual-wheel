namespace UART_demo
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
            this.textBoxReceive = new System.Windows.Forms.TextBox();
            this.textBoxSend = new System.Windows.Forms.TextBox();
            this.comboBoxPort = new System.Windows.Forms.ComboBox();
            this.comboBoxBaudrate = new System.Windows.Forms.ComboBox();
            this.comboBoxDataBits = new System.Windows.Forms.ComboBox();
            this.comboBoxStopBits = new System.Windows.Forms.ComboBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.buttonOpenPort = new System.Windows.Forms.Button();
            this.buttonClearDisplay = new System.Windows.Forms.Button();
            this.attitudeDisplay1 = new AttitudeDisplay.AttitudeDisplay();
            this.SuspendLayout();
            // 
            // textBoxReceive
            // 
            this.textBoxReceive.Font = new System.Drawing.Font("SimSun", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBoxReceive.Location = new System.Drawing.Point(469, 13);
            this.textBoxReceive.MaxLength = 655355;
            this.textBoxReceive.Multiline = true;
            this.textBoxReceive.Name = "textBoxReceive";
            this.textBoxReceive.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxReceive.Size = new System.Drawing.Size(204, 358);
            this.textBoxReceive.TabIndex = 0;
            this.textBoxReceive.WordWrap = false;
            // 
            // textBoxSend
            // 
            this.textBoxSend.Location = new System.Drawing.Point(469, 458);
            this.textBoxSend.Name = "textBoxSend";
            this.textBoxSend.Size = new System.Drawing.Size(204, 21);
            this.textBoxSend.TabIndex = 3;
            // 
            // comboBoxPort
            // 
            this.comboBoxPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxPort.FormattingEnabled = true;
            this.comboBoxPort.Location = new System.Drawing.Point(13, 429);
            this.comboBoxPort.Name = "comboBoxPort";
            this.comboBoxPort.Size = new System.Drawing.Size(84, 20);
            this.comboBoxPort.TabIndex = 4;
            this.comboBoxPort.DropDown += new System.EventHandler(this.comboBoxPort_DropDown);
            // 
            // comboBoxBaudrate
            // 
            this.comboBoxBaudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxBaudrate.FormattingEnabled = true;
            this.comboBoxBaudrate.Location = new System.Drawing.Point(109, 429);
            this.comboBoxBaudrate.Name = "comboBoxBaudrate";
            this.comboBoxBaudrate.Size = new System.Drawing.Size(83, 20);
            this.comboBoxBaudrate.TabIndex = 5;
            // 
            // comboBoxDataBits
            // 
            this.comboBoxDataBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDataBits.FormattingEnabled = true;
            this.comboBoxDataBits.Location = new System.Drawing.Point(14, 459);
            this.comboBoxDataBits.Name = "comboBoxDataBits";
            this.comboBoxDataBits.Size = new System.Drawing.Size(83, 20);
            this.comboBoxDataBits.TabIndex = 6;
            // 
            // comboBoxStopBits
            // 
            this.comboBoxStopBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxStopBits.FormattingEnabled = true;
            this.comboBoxStopBits.Location = new System.Drawing.Point(109, 459);
            this.comboBoxStopBits.Name = "comboBoxStopBits";
            this.comboBoxStopBits.Size = new System.Drawing.Size(83, 20);
            this.comboBoxStopBits.TabIndex = 7;
            // 
            // buttonSend
            // 
            this.buttonSend.Location = new System.Drawing.Point(598, 429);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(75, 23);
            this.buttonSend.TabIndex = 10;
            this.buttonSend.Text = "发送";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // buttonOpenPort
            // 
            this.buttonOpenPort.Location = new System.Drawing.Point(208, 426);
            this.buttonOpenPort.Name = "buttonOpenPort";
            this.buttonOpenPort.Size = new System.Drawing.Size(75, 23);
            this.buttonOpenPort.TabIndex = 12;
            this.buttonOpenPort.Text = "打开串口";
            this.buttonOpenPort.UseVisualStyleBackColor = true;
            this.buttonOpenPort.Click += new System.EventHandler(this.buttonOpenPort_Click);
            // 
            // buttonClearDisplay
            // 
            this.buttonClearDisplay.Location = new System.Drawing.Point(598, 377);
            this.buttonClearDisplay.Name = "buttonClearDisplay";
            this.buttonClearDisplay.Size = new System.Drawing.Size(75, 23);
            this.buttonClearDisplay.TabIndex = 13;
            this.buttonClearDisplay.Text = "清除窗口";
            this.buttonClearDisplay.UseVisualStyleBackColor = true;
            this.buttonClearDisplay.Click += new System.EventHandler(this.buttonClearDisplay_Click);
            // 
            // attitudeDisplay1
            // 
            this.attitudeDisplay1.Location = new System.Drawing.Point(14, 13);
            this.attitudeDisplay1.Name = "attitudeDisplay1";
            this.attitudeDisplay1.Size = new System.Drawing.Size(429, 387);
            this.attitudeDisplay1.TabIndex = 14;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(685, 488);
            this.Controls.Add(this.attitudeDisplay1);
            this.Controls.Add(this.buttonClearDisplay);
            this.Controls.Add(this.buttonOpenPort);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.comboBoxStopBits);
            this.Controls.Add(this.comboBoxDataBits);
            this.Controls.Add(this.comboBoxBaudrate);
            this.Controls.Add(this.comboBoxPort);
            this.Controls.Add(this.textBoxSend);
            this.Controls.Add(this.textBoxReceive);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "串口工具";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxReceive;
        private System.Windows.Forms.TextBox textBoxSend;
        private System.Windows.Forms.ComboBox comboBoxPort;
        private System.Windows.Forms.ComboBox comboBoxBaudrate;
        private System.Windows.Forms.ComboBox comboBoxDataBits;
        private System.Windows.Forms.ComboBox comboBoxStopBits;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.Button buttonOpenPort;
        private System.Windows.Forms.Button buttonClearDisplay;
        private AttitudeDisplay.AttitudeDisplay attitudeDisplay1;
    }
}

