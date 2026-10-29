using System;
using System.Threading.Tasks;

namespace image_threshold_lab3
{
    public static class Thresholding
    {
        static long[] Hist(GrayBuffer g)
        {
            var h = new long[256];
            for (int i = 0; i < g.Data.Length; i++) h[g.Data[i]]++;
            return h;
        }

        public static int Otsu(GrayBuffer g)
        {
            var h = Hist(g);
            long total = g.Data.Length;
            double sumAll = 0;
            for (int i = 0; i < 256; i++) sumAll += (double)i * h[i];

            double sumB = 0, best = -1; long wB = 0; int t = 0;
            for (int i = 0; i < 256; i++)
            {
                wB += h[i];
                if (wB == 0) continue;
                long wF = total - wB;
                if (wF == 0) break;
                sumB += (double)i * h[i];
                double mB = sumB / wB, mF = (sumAll - sumB) / wF;
                double between = (double)wB * wF * (mB - mF) * (mB - mF);
                if (between > best) { best = between; t = i; }
            }
            return t;
        }

        public static int Iterative(GrayBuffer g)
        {
            var h = Hist(g);
            double sum = 0; long cnt = g.Data.Length;
            for (int i = 0; i < 256; i++) sum += (double)i * h[i];
            double t = sum / cnt;
            for (int iter = 0; iter < 200; iter++)
            {
                double s1 = 0, s2 = 0; long n1 = 0, n2 = 0;
                for (int i = 0; i < 256; i++)
                {
                    if (i <= t) { s1 += (double)i * h[i]; n1 += h[i]; }
                    else { s2 += (double)i * h[i]; n2 += h[i]; }
                }
                if (n1 == 0 || n2 == 0) break;
                double nt = (s1 / n1 + s2 / n2) / 2.0;
                if (Math.Abs(nt - t) < 0.5) { t = nt; break; }
                t = nt;
            }
            return (int)Math.Round(t);
        }

        public static ImageBuffer ApplyGlobal(GrayBuffer g, int t)
        {
            var dst = new ImageBuffer(g.Width, g.Height);
            Parallel.For(0, g.Height, y =>
            {
                for (int x = 0; x < g.Width; x++)
                {
                    byte v = g.Data[y * g.Width + x] > t ? (byte)255 : (byte)0;
                    int o = (y * g.Width + x) * 4;
                    dst.Data[o] = dst.Data[o + 1] = dst.Data[o + 2] = v; dst.Data[o + 3] = 255;
                }
            });
            return dst;
        }

        public static ImageBuffer Adaptive(GrayBuffer g, int r, double k)
        {
            int w = g.Width, h = g.Height;
            var pad = g.Padded(r);
            int pw = pad.Width, ph = pad.Height, iw = pw + 1;

            var I = new long[iw * (ph + 1)];
            var I2 = new long[iw * (ph + 1)];
            for (int y = 0; y < ph; y++)
            {
                long rs = 0, rq = 0;
                for (int x = 0; x < pw; x++)
                {
                    long v = pad.Data[y * pw + x];
                    rs += v; rq += v * v;
                    int idx = (y + 1) * iw + (x + 1);
                    I[idx] = I[y * iw + (x + 1)] + rs;
                    I2[idx] = I2[y * iw + (x + 1)] + rq;
                }
            }

            int win = 2 * r + 1;
            double area = (double)win * win;
            var dst = new ImageBuffer(w, h);

            Parallel.For(0, h, y =>
            {
                for (int x = 0; x < w; x++)
                {
                    int y0 = y * iw, y1 = (y + win) * iw, x0 = x, x1 = x + win;
                    long s = I[y1 + x1] - I[y0 + x1] - I[y1 + x0] + I[y0 + x0];
                    long q = I2[y1 + x1] - I2[y0 + x1] - I2[y1 + x0] + I2[y0 + x0];

                    double m = s / area;
                    double std = Math.Sqrt(Math.Max(q / area - m * m, 0.0));
                    double T = m * (1 + k * (std / 128.0 - 1));

                    int i = y * w + x;
                    byte v = g.Data[i] > T ? (byte)255 : (byte)0;
                    int o = i * 4;
                    dst.Data[o] = dst.Data[o + 1] = dst.Data[o + 2] = v; dst.Data[o + 3] = 255;
                }
            });
            return dst;
        }
    }
}