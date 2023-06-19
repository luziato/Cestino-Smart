using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows.Forms;
using Windows.Gaming.Input;

using System.Net.Sockets;
using System.Net;

using ChatApplication;

namespace ChatClient
{
    public partial class Client : Form
    {

        Gamepad Controller;         //controller for moving the bin
        Timer t = new Timer();

        #region Private Members

        // Client socket
        private Socket clientSocket;

        // Client name
        private string name;

        // Server End Point
        private EndPoint epServer;

        // Data stream
        private byte[] dataStream = new byte[1024];

        // Display message delegate
        private delegate void DisplayMessageDelegate(string message);
        private DisplayMessageDelegate displayMessageDelegate = null;

        #endregion

        #region Constructor

        public Client()
        {
            InitializeComponent();
            Gamepad.GamepadAdded += Gamepad_GamepadAdded;
            Gamepad.GamepadRemoved += Gamepad_GamepadRemoved;


            t.Tick += T_Tick;
            t.Interval = (int)nudTempo.Value;
            t.Start();
        }

        private async void T_Tick(object sender, EventArgs e)
        {

            if (Gamepad.Gamepads.Count > 0)
            {
                Controller = Gamepad.Gamepads.First();
                var Reading = Controller.GetCurrentReading();

                

                switch (Reading.Buttons)
                {                                       
                    
                             //90° angle aka N,S,E,O

                    case GamepadButtons.DPadUp:
                        await Log("NORD was pressed");

                        try
                        {
                            // Initialise a packet object to store the data to be sent
                            Packet sendData = new Packet();
                            sendData.ChatName = this.name;
                            sendData.ChatMessage = "0;" + nudVel.Value + ";" + nudTempo.Value + ";";
                            sendData.ChatDataIdentifier = DataIdentifier.Message;

                            // Get packet as byte array
                            byte[] byteData = sendData.GetDataStream();

                            // Send packet to the server
                            clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                            //txtMessage.Text = string.Empty;
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }

                        break;

                    case GamepadButtons.DPadDown:
                        await Log("SUD was pressed");

                        try
                        {
                            // Initialise a packet object to store the data to be sent
                            Packet sendData = new Packet();
                            sendData.ChatName = this.name;
                            sendData.ChatMessage = "180;" + nudVel.Value + ";" + nudTempo.Value + ";";
                            sendData.ChatDataIdentifier = DataIdentifier.Message;

                            // Get packet as byte array
                            byte[] byteData = sendData.GetDataStream();

                            // Send packet to the server
                            clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                            //txtMessage.Text = string.Empty;
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }

                        break;

                    case GamepadButtons.DPadLeft:
                        await Log("OVEST was pressed");

                        try
                        {
                            // Initialise a packet object to store the data to be sent
                            Packet sendData = new Packet();
                            sendData.ChatName = this.name;
                            sendData.ChatMessage = "270;" + nudVel.Value + ";" + nudTempo.Value + ";";
                            sendData.ChatDataIdentifier = DataIdentifier.Message;

                            // Get packet as byte array
                            byte[] byteData = sendData.GetDataStream();

                            // Send packet to the server
                            clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                            //txtMessage.Text = string.Empty;
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }

                        break;

                    case GamepadButtons.DPadRight:
                        await Log("EST was pressed");

                        try
                        {
                            // Initialise a packet object to store the data to be sent
                            Packet sendData = new Packet();
                            sendData.ChatName = this.name;
                            sendData.ChatMessage = "90;" + nudVel.Value + ";" + nudTempo.Value + ";";
                            sendData.ChatDataIdentifier = DataIdentifier.Message;

                            // Get packet as byte array
                            byte[] byteData = sendData.GetDataStream();

                            // Send packet to the server
                            clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                            //txtMessage.Text = string.Empty;
                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        }

                        break;

                             //45° angle aka NE,SE,SO,NO

                    //case var n when GamepadButtons.DPadUp & GamepadButtons.DPadRight :
                    //    await Log("NORD-EST was pressed");
                    //    break;

                    //case GamepadButtons.DPadDown:
                    //case GamepadButtons.DPadRight:
                    //    await Log("SUD-EST was pressed");
                    //    break;

                    //case GamepadButtons.DPadDown:
                    //case GamepadButtons.DPadLeft:
                    //    await Log("SUD-OVEST was pressed");
                    //    break;

                    //case GamepadButtons.DPadUp:
                    //case GamepadButtons.DPadLeft:
                    //    await Log("NORD-OVEST was pressed");
                    //    break;
                }
            }
        }

        private async void Gamepad_GamepadRemoved(object sender, Gamepad e)
        {
            await Log("controller removed");
        }

        private async void Gamepad_GamepadAdded(object sender, Gamepad e)
        {
            await Log("controller added");
        }

        private async Task Log(string txt)
        {
            Task t = Task.Run(() =>
            {
                Debug.WriteLine(DateTime.Now.ToShortTimeString() + ": " + txt);

            });
            await t;
        }

        #endregion

        #region Events 

        private void Client_Load(object sender, EventArgs e)
        {
            // Initialise delegate
            this.displayMessageDelegate = new DisplayMessageDelegate(this.DisplayMessage);
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            try
            {
                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = txtMessage.Text.Trim();
                sendData.ChatDataIdentifier = DataIdentifier.Message;

                // Get packet as byte array
                byte[] byteData = sendData.GetDataStream();

                // Send packet to the server
                clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                txtMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Client_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (this.clientSocket != null)
                {
                    // Initialise a packet object to store the data to be sent
                    Packet sendData = new Packet();
                    sendData.ChatDataIdentifier = DataIdentifier.LogOut;
                    sendData.ChatName = this.name;
                    sendData.ChatMessage = null;

                    // Get packet as byte array
                    byte[] byteData = sendData.GetDataStream();

                    // Send packet to the server
                    this.clientSocket.SendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer);

                    // Close the socket
                    this.clientSocket.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Closing Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                this.name = txtName.Text.Trim();

                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = null;
                sendData.ChatDataIdentifier = DataIdentifier.LogIn;

                // Initialise socket
                this.clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

                // Initialise server IP
                IPAddress serverIP = IPAddress.Parse(txtServerIP.Text.Trim());

                // Initialise the IPEndPoint for the server and use port 30000
                IPEndPoint server = new IPEndPoint(serverIP, 30000);

                // Initialise the EndPoint for the server
                epServer = (EndPoint)server;

                // Get packet as byte array
                byte[] data = sendData.GetDataStream();

                // Send data to server
                clientSocket.BeginSendTo(data, 0, data.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                // Initialise data stream
                this.dataStream = new byte[1024];

                // Begin listening for broadcasts
                clientSocket.BeginReceiveFrom(this.dataStream, 0, this.dataStream.Length, SocketFlags.None, ref epServer, new AsyncCallback(this.ReceiveData), null);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region Send And Receive

        private void SendData(IAsyncResult ar)
        {
            try
            {
                clientSocket.EndSend(ar);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Data: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ReceiveData(IAsyncResult ar)
        {
            try
            {
                // Receive all data
                this.clientSocket.EndReceive(ar);

                // Initialise a packet object to store the received data
                Packet receivedData = new Packet(this.dataStream);

                // Update display through a delegate
                if (receivedData.ChatMessage != null)
                    this.Invoke(this.displayMessageDelegate, new object[] { receivedData.ChatMessage });

                // Reset data stream
                this.dataStream = new byte[1024];

                // Continue listening for broadcasts
                clientSocket.BeginReceiveFrom(this.dataStream, 0, this.dataStream.Length, SocketFlags.None, ref epServer, new AsyncCallback(this.ReceiveData), null);
            }
            catch (ObjectDisposedException)
            { }
            catch (Exception ex)
            {
                MessageBox.Show("Receive Data: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Other Methods

        private void DisplayMessage(string messge)
        {
            rtxtConversation.Text += messge + Environment.NewLine;
        }

        #endregion

        private void btnAvanti_Click_1(object sender, EventArgs e)
        {
            try
            {
                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = "NORD;" + nudVel.Value + ";" + nudTempo.Value + ";";
                sendData.ChatDataIdentifier = DataIdentifier.Message;

                // Get packet as byte array
                byte[] byteData = sendData.GetDataStream();

                // Send packet to the server
                clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                //txtMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnDX_Click(object sender, EventArgs e)
        {
            try
            {
                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = "EST;" + nudVel.Value + ";" + nudTempo.Value + ";";
                sendData.ChatDataIdentifier = DataIdentifier.Message;

                // Get packet as byte array
                byte[] byteData = sendData.GetDataStream();

                // Send packet to the server
                clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                //txtMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnIndietro_Click(object sender, EventArgs e)
        {
            try
            {
                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = "SUD;" + nudVel.Value + ";" + nudTempo.Value + ";";
                sendData.ChatDataIdentifier = DataIdentifier.Message;

                // Get packet as byte array
                byte[] byteData = sendData.GetDataStream();

                // Send packet to the server
                clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                //txtMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnSX_Click(object sender, EventArgs e)
        {
            try
            {
                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = "OVEST;" + nudVel.Value + ";" + nudTempo.Value + ";";
                sendData.ChatDataIdentifier = DataIdentifier.Message;

                // Get packet as byte array
                byte[] byteData = sendData.GetDataStream();

                // Send packet to the server
                clientSocket.BeginSendTo(byteData, 0, byteData.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                //txtMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            try
            {
                this.name = txtName.Text.Trim();

                // Initialise a packet object to store the data to be sent
                Packet sendData = new Packet();
                sendData.ChatName = this.name;
                sendData.ChatMessage = null;
                sendData.ChatDataIdentifier = DataIdentifier.LogOut;
                // Initialise socket
                this.clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

                // Initialise server IP
                IPAddress serverIP = IPAddress.Parse(txtServerIP.Text.Trim());

                // Initialise the IPEndPoint for the server and use port 30000
                IPEndPoint server = new IPEndPoint(serverIP, 30000);

                // Initialise the EndPoint for the server
                epServer = (EndPoint)server;

                // Get packet as byte array
                byte[] data = sendData.GetDataStream();

                // Send data to server
                clientSocket.BeginSendTo(data, 0, data.Length, SocketFlags.None, epServer, new AsyncCallback(this.SendData), null);

                // Initialise data stream
                this.dataStream = new byte[1024];

                // Begin listening for broadcasts
                clientSocket.BeginReceiveFrom(this.dataStream, 0, this.dataStream.Length, SocketFlags.None, ref epServer, new AsyncCallback(this.ReceiveData), null);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Connection Error: " + ex.Message, "UDP Client", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            rtxtConversation.Text = "";
        }

    }


    #region old: analog conversion from cartesian to polar

    //public class convert
    //{
    //    public float x, y;

    //    public double toPolarRadius(int x, int y)
    //    {
    //        double r = Math.Round(Math.Sqrt(x * x + y * y), 2);      //calculate de radius/module form the cartesian point

    //        return r;
    //    }

    //    public double toPolarAngle(int x, int y)
    //    {
    //        double theta = Math.Atan(y / x);     //calculate the angle form the cartesian point
    //        theta = 180.0 * theta / 3.141;      //Convert the angle form rad to deg

    //        return theta;
    //    }

    //}

    #endregion


}
