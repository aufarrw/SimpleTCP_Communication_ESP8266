using System;
using System.Text;
using System.Windows.Forms;
using SimpleTCP;

namespace Client
{
    public partial class Form1 : Form
    {
        SimpleTcpClient client;
        public Form1()
        {
            InitializeComponent();
        }

        private void btnConn_Click(object sender, EventArgs e)
        {
            client.Connect(tbIP.Text, Convert.ToInt32(tbPort.Text));
            rtbSend.ReadOnly = false;
            btnConn.Enabled = false;
            btnSend.Enabled = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            client = new SimpleTcpClient();
            client.StringEncoder = Encoding.UTF8;
            client.DataReceived += Client_DataReceived;
            rtbSend.ReadOnly = true;
            btnSend.Enabled = false;
        }

        private void Client_DataReceived(object sender, SimpleTCP.Message e)
        {
            rtbRec.Invoke((MethodInvoker)delegate ()
            {
                rtbRec.Text += e.MessageString;
            });
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            client.WriteLine(rtbSend.Text);
        }
    }
}