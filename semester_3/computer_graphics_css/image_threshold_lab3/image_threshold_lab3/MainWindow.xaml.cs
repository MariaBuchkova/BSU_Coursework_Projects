using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Microsoft.Win32;

namespace image_threshold_lab3
{
    public partial class MainWindow : Window
    {
        int W, H;
        ImageBuffer currentImg;
        ImageBuffer resultImg;

        public MainWindow()
        {
            InitializeComponent();
        }

        void Open_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new OpenFileDialog { Filter = "Изображения|*.png;*.jpg;*.jpeg;*.bmp" };
            if (dlg.ShowDialog() != true) return;

            var bi = new BitmapImage();
            bi.BeginInit();
            bi.CacheOption = BitmapCacheOption.OnLoad;
            bi.UriSource = new Uri(dlg.FileName);
            bi.EndInit();

            var conv = new FormatConvertedBitmap(bi, PixelFormats.Bgra32, null, 0);
            W = conv.PixelWidth;
            H = conv.PixelHeight;

            currentImg = new ImageBuffer(W, H);
            conv.CopyPixels(currentImg.Data, W * 4, 0);

            resultImg = null;
            ImgBefore.Source = MakeBitmap(currentImg);
            ImgAfter.Source = null;
            Status.Text = W + "×" + H;
        }

        BitmapSource MakeBitmap(ImageBuffer img)
        {
            return BitmapSource.Create(img.Width, img.Height, 96, 96, PixelFormats.Bgra32, null, img.Data, img.Stride);
        }

        void Promote_Click(object sender, RoutedEventArgs e)
        {
            if (resultImg == null) return;
            currentImg = resultImg;
            resultImg = null;
            W = currentImg.Width;
            H = currentImg.Height;
            ImgBefore.Source = MakeBitmap(currentImg);
            ImgAfter.Source = null;
        }

        void Save_Click(object sender, RoutedEventArgs e)
        {
            if (resultImg == null) return;
            var dlg = new SaveFileDialog { Filter = "PNG|*.png" };
            if (dlg.ShowDialog() != true) return;

            var enc = new PngBitmapEncoder();
            enc.Frames.Add(BitmapFrame.Create(MakeBitmap(resultImg)));
            using (var fs = System.IO.File.Create(dlg.FileName))
                enc.Save(fs);
        }

        bool HasImage()
        {
            if (currentImg == null)
            {
                MessageBox.Show("Сначала откройте изображение.");
                return false;
            }
            return true;
        }

        void ShowResult(ImageBuffer img, string info)
        {
            resultImg = img;
            ImgAfter.Source = MakeBitmap(resultImg);
            Status.Text = info;
        }

        void ResetResult()
        {
            resultImg = null;
            if (ImgAfter != null) ImgAfter.Source = null;
            if (Status != null && currentImg != null) Status.Text = currentImg.Width + "×" + currentImg.Height;
        }

        void Tabs_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.Source != Tabs) return; 
            ResetResult();
        }

        void PointOp_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (PointParamPanel == null) return;
            string op = ((ComboBoxItem)PointOp.SelectedItem).Tag.ToString();
            PointParamPanel.IsEnabled = op != "neg";
            ResetResult();
        }

        void ThrMethod_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (AdaptPanel == null) return;
            string m = ((ComboBoxItem)ThrMethod.SelectedItem).Tag.ToString();
            AdaptPanel.IsEnabled = m == "adapt";
            ResetResult();
        }

        void ApplyPoint_Click(object sender, RoutedEventArgs e)
        {
            if (!HasImage()) return;
            string op = ((ComboBoxItem)PointOp.SelectedItem).Tag.ToString();
            double p = PointParam.Value;

            if (op == "bright")
            {
                resultImg = PointOps.Brightness(currentImg, p);
                ShowResult(resultImg, $"Яркость: сдвиг {p:F0}");
            }
            else if (op == "gamma")
            {
                double gammaVal = Math.Pow(2, p / 50.0);
                resultImg = PointOps.Gamma(currentImg, gammaVal);
                ShowResult(resultImg, $"Гамма: γ = {gammaVal:F2}");
            }
            else if (op == "neg")
            {
                resultImg = PointOps.Negative(currentImg);
                ShowResult(resultImg, "Негатив");
            }
        }

        void ApplyContrast_Click(object sender, RoutedEventArgs e)
        {
            if (!HasImage()) return;
            double cut = CutPct.Value;
            resultImg = PointOps.LinearContrast(currentImg, cut, cut, out string info);
            ShowResult(resultImg, "Линейное контрастирование: " + info);
        }

        void ApplyThreshold_Click(object sender, RoutedEventArgs e)
        {
            if (!HasImage()) return;
            string m = ((ComboBoxItem)ThrMethod.SelectedItem).Tag.ToString();

            GrayBuffer gray = currentImg.ToGray();

            if (m == "otsu")
            {
                int t = Thresholding.Otsu(gray);
                resultImg = Thresholding.ApplyGlobal(gray, t);
                ShowResult(resultImg, "Оцу: T = " + t);
            }
            else if (m == "iter")
            {
                int t = Thresholding.Iterative(gray);
                resultImg = Thresholding.ApplyGlobal(gray, t);
                ShowResult(resultImg, "Итеративный: T = " + t);
            }
            else if (m == "adapt")
            {
                int r = (int)Radius.Value;
                double k = CParam.Value / 100.0;

                resultImg = Thresholding.Adaptive(gray, r, k);
                ShowResult(resultImg, $"Адаптивный (Sauvola): окно {2 * r + 1}×{2 * r + 1}, k = {k:F2}");
            }
        }
    }
}