
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Rfcomm;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

namespace SDKTemplate
{
    public sealed partial class Scenario1_ChatClient : Page
    {
        private MainPage rootPage = MainPage.Current;

        public ObservableCollection<RfcommChatDeviceDisplay> ResultCollection
        {
            get;
            private set;
        }

        private DeviceWatcher deviceWatcher = null;
        private StreamSocket chatSocket = null;
        private DataWriter chatWriter = null;
        private RfcommDeviceService chatService = null;
        private BluetoothDevice bluetoothDevice;

        public Scenario1_ChatClient()
        {
            this.InitializeComponent();
            App.Current.Suspending += App_Suspending;
            cChessBoard.SendEvent += SendEvent;
            cChessBoard.InitBoard();
        }

        private async void SendEvent(object sender, EventArgs e)
        {
            var msg = sender.ToString();
            try
            {
                if (msg.Length != 0)
                {
                    chatWriter.WriteUInt32((uint)msg.Length);
                    chatWriter.WriteString(msg);

                    ConversationList.Items.Add(msg);
                    await chatWriter.StoreAsync();
                }
            }
            catch (Exception ex) when ((uint)ex.HResult == 0x80072745)
            {
                rootPage.NotifyUser("Remote side disconnect: " + ex.HResult.ToString() + " - " + ex.Message,
                    NotifyType.StatusMessage);
            }
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            rootPage = MainPage.Current;
            ResultCollection = new ObservableCollection<RfcommChatDeviceDisplay>();
            DataContext = this;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            StopWatcher();
        }

        private void StopWatcher()
        {
            if (null != deviceWatcher)
            {
                if ((DeviceWatcherStatus.Started == deviceWatcher.Status ||
                     DeviceWatcherStatus.EnumerationCompleted == deviceWatcher.Status))
                {
                    deviceWatcher.Stop();
                }
                deviceWatcher = null;
            }
        }

        void App_Suspending(object sender, Windows.ApplicationModel.SuspendingEventArgs e)
        {
            Disconnect("App Suspension disconnects");
        }

        private void RunButton_Click(object sender, RoutedEventArgs e)
        {
            if (deviceWatcher == null)
            {
                SetDeviceWatcherUI();
                StartUnpairedDeviceWatcher();
            }
            else
            {
                ResetMainUI();
            }
        }

        private void SetDeviceWatcherUI()
        {
            RunButton.Content = "Stop";
            rootPage.NotifyUser("Device watcher started", NotifyType.StatusMessage);
            resultsListView.Visibility = Visibility.Visible;
            resultsListView.IsEnabled = true;
        }

        private void ResetMainUI()
        {
            RunButton.Content = "Start";
            RunButton.IsEnabled = true;
            ConnectButton.Visibility = Visibility.Visible;
            resultsListView.Visibility = Visibility.Visible;
            resultsListView.IsEnabled = true;

            ChatBox.Visibility = Visibility.Collapsed;
            RequestAccessButton.Visibility = Visibility.Collapsed;
            if (ConversationList.Items != null) ConversationList.Items.Clear();
            StopWatcher();
        }

        private void StartUnpairedDeviceWatcher()
        {
            string[] requestedProperties = new string[] { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected" };

            deviceWatcher = DeviceInformation.CreateWatcher("(System.Devices.Aep.ProtocolId:=\"{e0cbf06c-cd8b-4647-bb8a-263b43f0f974}\")",
                                                            requestedProperties,
                                                            DeviceInformationKind.AssociationEndpoint);

            deviceWatcher.Added += new TypedEventHandler<DeviceWatcher, DeviceInformation>(async (watcher, deviceInfo) =>
            {
                await rootPage.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    if(deviceInfo.Name != "")
                    {
                        ResultCollection.Add(new RfcommChatDeviceDisplay(deviceInfo));
                        rootPage.NotifyUser(
                            String.Format("{0} devices found.", ResultCollection.Count),
                            NotifyType.StatusMessage);
                    }

                });
            });

            deviceWatcher.Updated += new TypedEventHandler<DeviceWatcher, DeviceInformationUpdate>(async (watcher, deviceInfoUpdate) =>
            {
                await rootPage.Dispatcher.RunAsync(CoreDispatcherPriority.Low, () =>
                {
                    foreach (RfcommChatDeviceDisplay rfcommInfoDisp in ResultCollection)
                    {
                        if (rfcommInfoDisp.Id == deviceInfoUpdate.Id)
                        {
                            rfcommInfoDisp.Update(deviceInfoUpdate);
                            break;
                        }
                    }
                });
            });

            deviceWatcher.EnumerationCompleted += new TypedEventHandler<DeviceWatcher, Object>(async (watcher, obj) =>
            {
                await rootPage.Dispatcher.RunAsync(CoreDispatcherPriority.Low, () =>
                {
                    rootPage.NotifyUser(
                        String.Format("{0} devices found. Enumeration completed. Watching for updates...", ResultCollection.Count),
                        NotifyType.StatusMessage);
                });
            });

            deviceWatcher.Removed += new TypedEventHandler<DeviceWatcher, DeviceInformationUpdate>(async (watcher, deviceInfoUpdate) =>
            {
                await rootPage.Dispatcher.RunAsync(CoreDispatcherPriority.Low, () =>
                {
                    foreach (RfcommChatDeviceDisplay rfcommInfoDisp in ResultCollection)
                    {
                        if (rfcommInfoDisp.Id == deviceInfoUpdate.Id)
                        {
                            ResultCollection.Remove(rfcommInfoDisp);
                            break;
                        }
                    }

                    rootPage.NotifyUser(
                        String.Format("{0} devices found.", ResultCollection.Count),
                        NotifyType.StatusMessage);
                });
            });

            deviceWatcher.Stopped += new TypedEventHandler<DeviceWatcher, Object>(async (watcher, obj) =>
            {
                await rootPage.Dispatcher.RunAsync(CoreDispatcherPriority.Low, () =>
                {
                    ResultCollection.Clear();
                });
            });

            deviceWatcher.Start();
        }

       
        private async void ConnectButton_Click(object sender, RoutedEventArgs e)
        {
            // Make sure user has selected a device first
            if (resultsListView.SelectedItem != null)
            {
                rootPage.NotifyUser("Connecting to remote device. Please wait...", NotifyType.StatusMessage);
            }
            else
            {
                rootPage.NotifyUser("Please select an item to connect to", NotifyType.ErrorMessage);
                return;
            }

            RfcommChatDeviceDisplay deviceInfoDisp = resultsListView.SelectedItem as RfcommChatDeviceDisplay;

           
            DeviceAccessStatus accessStatus = DeviceAccessInformation.CreateFromId(deviceInfoDisp.Id).CurrentStatus;
            if (accessStatus == DeviceAccessStatus.DeniedByUser)
            {
                rootPage.NotifyUser("This app does not have access to connect to the remote device (please grant access in Settings > Privacy > Other Devices", NotifyType.ErrorMessage);
                return;
            }

            try
            {
                bluetoothDevice = await BluetoothDevice.FromIdAsync(deviceInfoDisp.Id);
            }
            catch (Exception ex)
            {
                rootPage.NotifyUser(ex.Message, NotifyType.ErrorMessage);
                ResetMainUI();
                return;
            }

            if (bluetoothDevice == null)
            {
                rootPage.NotifyUser("Bluetooth Device returned null. Access Status = " + accessStatus.ToString(), NotifyType.ErrorMessage);
            }

            var rfcommServices = await bluetoothDevice.GetRfcommServicesForIdAsync(
                RfcommServiceId.FromUuid(Constants.BTChessUuid), BluetoothCacheMode.Uncached);

            if (rfcommServices.Services.Count > 0)
            {
                chatService = rfcommServices.Services[0];
            }
            else
            {
                rootPage.NotifyUser(
                   "Could not discover the chat service on the remote device",
                   NotifyType.StatusMessage);
                ResetMainUI();
                return;
            }

            // Do various checks of the SDP record to make sure you are talking to a device that actually supports the Bluetooth Rfcomm Chat Service
            var attributes = await chatService.GetSdpRawAttributesAsync();
            if (!attributes.ContainsKey(Constants.SdpServiceNameAttributeId))
            {
                rootPage.NotifyUser(
                    "The Chat service is not advertising the Service Name attribute (attribute id=0x100). " +
                    "Please verify that you are running the BluetoothRfcommChat server.",
                    NotifyType.ErrorMessage);
                ResetMainUI();
                return;
            }
            var attributeReader = DataReader.FromBuffer(attributes[Constants.SdpServiceNameAttributeId]);
            var attributeType = attributeReader.ReadByte();
            if (attributeType != Constants.SdpServiceNameAttributeType)
            {
                rootPage.NotifyUser(
                    "The Chat service is using an unexpected format for the Service Name attribute. " +
                    "Please verify that you are running the BluetoothRfcommChat server.",
                    NotifyType.ErrorMessage);
                ResetMainUI();
                return;
            }
            var serviceNameLength = attributeReader.ReadByte();

            // The Service Name attribute requires UTF-8 encoding.
            attributeReader.UnicodeEncoding = UnicodeEncoding.Utf8;

            StopWatcher();

            lock (this)
            {
                chatSocket = new StreamSocket();
            }
            try
            {
                await chatSocket.ConnectAsync(chatService.ConnectionHostName, chatService.ConnectionServiceName);

                SetChatUI(attributeReader.ReadString(serviceNameLength), bluetoothDevice.Name);
                chatWriter = new DataWriter(chatSocket.OutputStream);

                DataReader chatReader = new DataReader(chatSocket.InputStream);
                ReceiveStringLoop(chatReader);
            }
            catch (Exception ex) when ((uint)ex.HResult == 0x80070490) // ERROR_ELEMENT_NOT_FOUND
            {
                rootPage.NotifyUser("Please verify that you are running the BluetoothRfcommChat server.", NotifyType.ErrorMessage);
                ResetMainUI();
            }
            catch (Exception ex) when ((uint)ex.HResult == 0x80072740) // WSAEADDRINUSE
            {
                rootPage.NotifyUser("Please verify that there is no other RFCOMM connection to the same device.", NotifyType.ErrorMessage);
                ResetMainUI();
            }
        }

        
        private async void RequestAccessButton_Click(object sender, RoutedEventArgs e)
        {
            // Make sure user has given consent to access device
            DeviceAccessStatus accessStatus = await bluetoothDevice.RequestAccessAsync();

            if (accessStatus != DeviceAccessStatus.Allowed)
            {
                rootPage.NotifyUser(
                    "Access to the device is denied because the application was not granted access",
                    NotifyType.StatusMessage);
            }
            else
            {
                rootPage.NotifyUser(
                                    "Access granted, you are free to pair devices",
                                    NotifyType.StatusMessage);
            }
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

        /// <summary>
        /// Takes the contents of the MessageTextBox and writes it to the outgoing chatWriter
        /// </summary>
        //private async void SendMessage()
        //{
        //    try
        //    {
        //        if (MessageTextBox.Text.Length != 0)
        //        {
        //            chatWriter.WriteUInt32((uint)MessageTextBox.Text.Length);
        //            chatWriter.WriteString(MessageTextBox.Text);

        //            ConversationList.Items.Add("Sent: " + MessageTextBox.Text);
        //            MessageTextBox.Text = "";
        //            await chatWriter.StoreAsync();

        //        }
        //    }
        //    catch (Exception ex) when ((uint)ex.HResult == 0x80072745)
        //    {
        //        // The remote device has disconnected the connection
        //        rootPage.NotifyUser("Remote side disconnect: " + ex.HResult.ToString() + " - " + ex.Message,
        //            NotifyType.StatusMessage);
        //    }
        //}

        private async void ReceiveStringLoop(DataReader chatReader)
        {
            try
            {
                uint size = await chatReader.LoadAsync(sizeof(uint));
                if (size < sizeof(uint))
                {
                    Disconnect("Remote device terminated connection - make sure only one instance of server is running on remote device");
                    return;
                }

                uint stringLength = chatReader.ReadUInt32();
                uint actualStringLength = await chatReader.LoadAsync(stringLength);
                if (actualStringLength != stringLength)
                {
                    // The underlying socket was closed before we were able to read the whole data
                    return;
                }

                //ConversationList.Items.Add(chatReader.ReadString(stringLength));
                //cChessBoard.UpdateBoard(chatReader.ReadString(stringLength));
                var message = chatReader.ReadString(stringLength);
                ConversationList.Items.Add(message);
                cChessBoard.UpdateBoard(message);
                ReceiveStringLoop(chatReader);
            }
            catch (Exception ex)
            {
                lock (this)
                {
                    if (chatSocket == null)
                    {
                        // Do not print anything here -  the user closed the socket.
                        if ((uint)ex.HResult == 0x80072745)
                            rootPage.NotifyUser("Disconnect triggered by remote device", NotifyType.StatusMessage);
                        else if ((uint)ex.HResult == 0x800703E3)
                            rootPage.NotifyUser("The I/O operation has been aborted because of either a thread exit or an application request.", NotifyType.StatusMessage);
                    }
                    else
                    {
                        Disconnect("Read stream failed with error: " + ex.Message);
                    }
                }
            }
        }

        private void DisconnectButton_Click(object sender, RoutedEventArgs e)
        {
            Disconnect("Disconnected");
        }



        private void Disconnect(string disconnectReason)
        {
            if (chatWriter != null)
            {
                chatWriter.DetachStream();
                chatWriter = null;
            }


            if (chatService != null)
            {
                chatService.Dispose();
                chatService = null;
            }
            lock (this)
            {
                if (chatSocket != null)
                {
                    chatSocket.Dispose();
                    chatSocket = null;
                }
            }

            rootPage.NotifyUser(disconnectReason, NotifyType.StatusMessage);
            ResetMainUI();
        }

        private void SetChatUI(string serviceName, string deviceName)
        {
            rootPage.NotifyUser("Connected", NotifyType.StatusMessage);
            ServiceName.Text = "Service Name: " + serviceName;
            DeviceName.Text = "Connected to: " + deviceName;
            RunButton.IsEnabled = false;
            ConnectButton.Visibility = Visibility.Collapsed;
            RequestAccessButton.Visibility = Visibility.Visible;
            resultsListView.IsEnabled = false;
            resultsListView.Visibility = Visibility.Collapsed;
            ChatBox.Visibility = Visibility.Visible;
        }

        private void ResultsListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            UpdatePairingButtons();
        }

        private void UpdatePairingButtons()
        {
            RfcommChatDeviceDisplay deviceDisp = (RfcommChatDeviceDisplay)resultsListView.SelectedItem;

            if (null != deviceDisp)
            {
                ConnectButton.IsEnabled = true;
            }
            else
            {
                ConnectButton.IsEnabled = false;
            }
        }
    }

    public class RfcommChatDeviceDisplay : INotifyPropertyChanged
    {
        private DeviceInformation deviceInfo;

        public RfcommChatDeviceDisplay(DeviceInformation deviceInfoIn)
        {
            deviceInfo = deviceInfoIn;
            UpdateGlyphBitmapImage();
        }

        public DeviceInformation DeviceInformation
        {
            get
            {
                return deviceInfo;
            }

            private set
            {
                deviceInfo = value;
            }
        }

        public string Id
        {
            get
            {
                return deviceInfo.Id;
            }
        }

        public string Name
        {
            get
            {
                return deviceInfo.Name;
            }
        }

        public BitmapImage GlyphBitmapImage
        {
            get;
            private set;
        }

        public void Update(DeviceInformationUpdate deviceInfoUpdate)
        {
            deviceInfo.Update(deviceInfoUpdate);
            UpdateGlyphBitmapImage();
        }

        private async void UpdateGlyphBitmapImage()
        {
            DeviceThumbnail deviceThumbnail = await deviceInfo.GetGlyphThumbnailAsync();
            BitmapImage glyphBitmapImage = new BitmapImage();
            await glyphBitmapImage.SetSourceAsync(deviceThumbnail);
            GlyphBitmapImage = glyphBitmapImage;
            OnPropertyChanged("GlyphBitmapImage");
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }
    }
}
