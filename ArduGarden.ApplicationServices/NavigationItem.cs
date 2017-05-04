namespace ArduGarden.ApplicationServices
{
    public class NavigationItem : ObservableObject
    {
        private string _name;
        private object _content;
        private object _icon;

        public string Name
        {
            get { return _name; }
            set
            {
                _name = value;
                OnPropertyChanged();
            }
        }

        public object Content
        {
            get { return _content; }
            set
            {
                _content = value;
                OnPropertyChanged();
            }
        }

        public object Icon
        {
            get { return _icon; }
            set
            {
                _icon = value;
                OnPropertyChanged();
            }
        }
    }
}
