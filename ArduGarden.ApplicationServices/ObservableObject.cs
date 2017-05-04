using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows.Threading;

namespace ArduGarden.ApplicationServices
{
    public abstract class ObservableObject : INotifyPropertyChanged
    {
        private readonly Dispatcher _dispatcher = Dispatcher.CurrentDispatcher;
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            _dispatcher.Invoke(() => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName)));
        }
    }
}
