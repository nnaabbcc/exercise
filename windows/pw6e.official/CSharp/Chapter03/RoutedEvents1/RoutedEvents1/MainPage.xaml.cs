using System;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace RoutedEvents1
{
    public sealed partial class MainPage : Page
    {
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnGridTapped(object sender, TappedRoutedEventArgs args)
        {
            if (args.OriginalSource is TextBlock)
            {
                TextBlock txtblk = args.OriginalSource as TextBlock;
                rand.NextBytes(rgb);
                Color clr = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);
                txtblk.Foreground = new SolidColorBrush(clr);
            }
        }
    }
}
