using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using MaterialDesignThemes.Wpf;

namespace ArduGarden.Views
{
    /// <summary>
    /// Interaction logic for GraphView.xaml
    /// </summary>
    public partial class GraphView : UserControl
    {
        public GraphView()
        {
            InitializeComponent();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            //var dialog = new ConnectDialog();
            //await DialogHost.Show(dialog, "RootDialog");
            MainSnackbar.MessageQueue.Enqueue("ArduGarden is connected!");
        }
    }
}
