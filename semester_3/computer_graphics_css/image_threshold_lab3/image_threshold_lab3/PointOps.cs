using System;
using System.Threading.Tasks;

namespace image_threshold_lab3
{
    public static class PointOps
    {
        static byte Clamp(double v) => (byte)(v < 0 ? 0 : v > 255 ? 255 : (int)(v + 0.5));
        static unsafe ImageBuffer ApplyTable(ImageBuffer src, byte[] lut)
        {
            var dst = new ImageBuffer(src.Width, src.Height);
            Parallel.For(0, src.Height, y =>
            {
                fixed (byte* ps = src.Data)
                fixed (byte* pd = dst.Data)
                {
                    byte* s = ps + y * src.Stride, d = pd + y * dst.Stride;
                    for (int x = 0; x < src.Width; x++, s += 4, d += 4)
                    {
                        d[0] = lut[s[0]];
                        d[1] = lut[s[1]];
                        d[2] = lut[s[2]];
                        d[3] = s[3];
                    }
                }
            });
            return dst;
        }
        static ImageBuffer ApplyLut(ImageBuffer src, Func<int, double> f)
        {
            var lut = new byte[256];
            for (int i = 0; i < 256; i++) lut[i] = Clamp(f(i));
            return ApplyTable(src, lut);
        }

        public static ImageBuffer Brightness(ImageBuffer s, double add) => ApplyLut(s, v => v + add);
        public static ImageBuffer Gamma(ImageBuffer s, double g) => ApplyLut(s, v => 255.0 * Math.Pow(v / 255.0, 1.0 / g));
        public static ImageBuffer Negative(ImageBuffer s) => ApplyLut(s, v => 255 - v);
        static unsafe long[] Histogram(ImageBuffer img)
        {
            var h = new long[256];
            fixed (byte* p0 = img.Data)
            {
                byte* p = p0;
                int n = img.Width * img.Height;
                for (int i = 0; i < n; i++, p += 4)
                    h[(p[0] * 114 + p[1] * 587 + p[2] * 299 + 500) / 1000]++;
            }
            return h;
        }

        static void Range(long[] h, long n, double lowPct, double highPct, out int lo, out int hi)
        {
            long cl = (long)(n * lowPct / 100.0), ch = (long)(n * highPct / 100.0);
            long c = 0; lo = 0;
            for (int i = 0; i < 256; i++) { c += h[i]; if (c > cl) { lo = i; break; } }
            c = 0; hi = 255;
            for (int i = 255; i >= 0; i--) { c += h[i]; if (c > ch) { hi = i; break; } }
            if (hi <= lo) { if (lo >= 255) lo = 254; hi = lo + 1; }
        }

        static byte[] StretchLut(int lo, int hi)
        {
            var lut = new byte[256];
            for (int i = 0; i < 256; i++) lut[i] = Clamp((i - lo) * 255.0 / (hi - lo));
            return lut;
        }

        public static ImageBuffer LinearContrast(ImageBuffer src, double lowPct, double highPct, out string info)
        {
            long n = (long)src.Width * src.Height;
            Range(Histogram(src), n, lowPct, highPct, out int lo, out int hi);
            info = $"диапазон яркости [{lo}; {hi}] → [0; 255]";
            return ApplyTable(src, StretchLut(lo, hi));
        }
    }
}