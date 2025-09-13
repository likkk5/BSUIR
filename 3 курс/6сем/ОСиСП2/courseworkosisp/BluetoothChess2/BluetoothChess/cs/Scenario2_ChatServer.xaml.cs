
using System;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Rfcomm;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Navigation;

namespace SDKTemplate
{
    public sealed partial class Scenario2_ChatServer : Page
    {
        private StreamSocket socket;
        private DataWriter writer;
        private RfcommServiceProvider rfcommProvider;
        private StreamSocketListener socketListener;

        MainPage rootPage;

        public Scenario2_ChatServer()
        {
            this.InitializeComponent();
            cChessBoard.SendEvent += SendEvent;
            cChessBoard.InitBoard(false);
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            rootPage = MainPage.Current;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            Disconnect();
        }

        private void ListenButton_Click(object sender, RoutedEventArgs e)
        {
            InitializeRfcommServer();
        }


        private async void InitializeRfcommServer()
        {
            ListenButton.IsEnabled = false;
            DisconnectButton.IsEnabled = true;

            try
            {
                rfcommProvider = await RfcommServiceProvider.CreateAsync(RfcommServiceId.FromUuid(Constants.BTChessUuid));
            }
            
            catch (Exception ex) when ((uint)ex.HResult == 0x800710DF)
            {

                rootPage.NotifyUser("Make sure your Bluetooth Radio is on: " + ex.Message, NotifyType.ErrorMessage);
                ListenButton.IsEnabled = true;
                DisconnectButton.IsEnabled = false;
                return;
            }
            

            
            socketListener = new StreamSocketListener();
            socketListener.ConnectionReceived += OnConnectionReceived;
            var rfcomm = rfcommProvider.ServiceId.AsString(); 

            await socketListener.BindServiceNameAsync(rfcommProvider.ServiceId.AsString(),
                SocketProtectionLevel.BluetoothEncryptionAllowNullAuthentication);

            
            InitializeServiceSdpAttributes(rfcommProvider);

            try
            {
                rfcommProvider.StartAdvertising(socketListener, true);
            }
            catch (Exception e)
            {
                rootPage.NotifyUser(e.Message, NotifyType.ErrorMessage);
                ListenButton.IsEnabled = true;
                DisconnectButton.IsEnabled = false;
                return;
            }
            
            rootPage.NotifyUser("Listening for incoming connections", NotifyType.StatusMessage);
        }

        private void InitializeServiceSdpAttributes(RfcommServiceProvider rfcommProvider)
        {
            var sdpWriter = new DataWriter();

            sdpWriter.WriteByte(Constants.SdpServiceNameAttributeType);

            sdpWriter.WriteByte((byte)Constants.SdpServiceName.Length);

            sdpWriter.UnicodeEncoding = Windows.Storage.Streams.UnicodeEncoding.Utf8;
            sdpWriter.WriteString(Constants.SdpServiceName);

            rfcommProvider.SdpRawAttributes.Add(Constants.SdpServiceNameAttributeId, sdpWriter.DetachBuffer());
        }

        //private void SendButton_Click(object sender, RoutedEventArgs e)
        //{
        //    SendMessage();
        //}

        //public void KeyboardKey_Pressed(object sender, KeyRoutedEventArgs e)
        //{
        //    if (e.Key == Windows.System.VirtualKey.Enter)
        //    {
        //        SendMessage();
        //    }
        //}

        private async void SendEvent(object sender, EventArgs e)
        {
            var msg = sender.ToString();
            if (msg.Length != 0)
            {
                if (socket != null)
                {
                    string message = msg;
                    writer.WriteUInt32((uint)message.Length);
                    writer.WriteString(message);

                    ConversationListBox.Items.Add(message);

                    await writer.StoreAsync();

                }
                else
                {
                    rootPage.NotifyUser("No clients connected, please wait for a client to connect before attempting to send a message", NotifyType.StatusMessage);
                }
            }
        }


        private void DisconnectButton_Click(object sender, RoutedEventArgs e)
        {
            Disconnect();
            rootPage.NotifyUser("Disconnected.", NotifyType.StatusMessage);
        }

        private async void Disconnect()
        {
            if (rfcommProvider != null)
            {
                rfcommProvider.StopAdvertising();
                rfcommProvider = null;
            }

            if (socketListener != null)
            {
                socketListener.Dispose();
                socketListener = null;
            }

            if (writer != null)
            {
                writer.DetachStream();
                writer = null;
            }

            if (socket != null)
            {
                socket.Dispose();
                socket = null;
            }
            await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
            {
                ListenButton.IsEnabled = true;
                DisconnectButton.IsEnabled = false;
                ConversationListBox.Items.Clear();
            });
        }

        private async void OnConnectionReceived(
            StreamSocketListener sender, StreamSocketListenerConnectionReceivedEventArgs args)
        {
            socketListener.Dispose();
            socketListener = null;

            try
            {
                socket = args.Socket;
            }
            catch (Exception e)
            {
                await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                {
                    rootPage.NotifyUser(e.Message, NotifyType.ErrorMessage);
                });
                Disconnect();
                return;
            }

            var remoteDevice = await BluetoothDevice.FromHostNameAsync(socket.Information.RemoteHostName);

            writer = new DataWriter(socket.OutputStream);
            var reader = new DataReader(socket.InputStream);
            bool remoteDisconnection = false;

            await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
            {
                rootPage.NotifyUser("Connected to Client: " + remoteDevice.Name, NotifyType.StatusMessage);
            });            

            // Infinite read buffer loop
            while (true)
            {
                try
                {
                    // Based on the protocol we've defined, the first uint is the size of the message
                    uint readLength = await reader.LoadAsync(sizeof(uint));

                    // Check if the size of the data is expected (otherwise the remote has already terminated the connection)
                    if (readLength < sizeof(uint))
                    {
                        remoteDisconnection = true;
                        break;
                    }
                    uint currentLength = reader.ReadUInt32();

                    // Load the rest of the message since you already know the length of the data expected.  
                    readLength = await reader.LoadAsync(currentLength);

                    // Check if the size of the data is expected (otherwise the remote has already terminated the connection)
                    if (readLength < currentLength)
                    {
                        remoteDisconnection = true;
                        break;
                    }
                    string message = reader.ReadString(currentLength);

                    await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                    {
                        ConversationListBox.Items.Add(message);
                        cChessBoard.UpdateBoard(message);
                    });
                }
                // Catch exception HRESULT_FROM_WIN32(ERROR_OPERATION_ABORTED).
                catch (Exception ex) when ((uint)ex.HResult == 0x800703E3)
                {
                    await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                    {
                        rootPage.NotifyUser("Client Disconnected Successfully", NotifyType.StatusMessage);
                    });
                    break;
                }
            }

            reader.DetachStream();
            if (remoteDisconnection)
            {
                Disconnect();
                await Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                {
                    rootPage.NotifyUser("Client disconnected",NotifyType.StatusMessage);
                });
            }
        }
    }
}
