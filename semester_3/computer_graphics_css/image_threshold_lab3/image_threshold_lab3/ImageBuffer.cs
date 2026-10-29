using System;
using System.Threading.Tasks;

namespace image_threshold_lab3
{
    public sealed class ImageBuffer
    {
        public readonly int Width, Height, Stride;
        public readonly byte[] Data;

        public ImageBuffer(int w, int h)
        {
            Width = w;
            Height = h;
            Stride = w * 4;
            Data = new byte[w * h * 4];
        }

        public unsafe GrayBuffer ToGray()
        {
            var g = new GrayBuffer(Width, Height);
            Parallel.For(0, Height, y =>
            {
                fixed (byte* ps = Data)
                fixed (byte* pd = g.Data)
                {
                    byte* s = ps + y * Stride;
                    byte* d = pd + y * Width;
                    for (int x = 0; x < Width; x++, s += 4)
                        d[x] = (byte)((s[0] * 114 + s[1] * 587 + s[2] * 299 + 500) / 1000);
                }
            });
            return g;
        }
    }

    public sealed class GrayBuffer
    {
        public readonly int Width, Height;
        public readonly byte[] Data;

        public GrayBuffer(int w, int h) { Width = w; Height = h; Data = new byte[w * h]; }
        public static int MapIndex(int i, int n)
        {
            if (i >= 0 && i < n) return i;
            if (n == 1) return 0;
            int p = 2 * n;
            i %= p; if (i < 0) i += p;
            return i < n ? i : p - 1 - i;
        }
        public GrayBuffer Padded(int r)
        {
            int pw = Width + 2 * r, ph = Height + 2 * r;
            var p = new GrayBuffer(pw, ph);
            Parallel.For(0, ph, py =>
            {
                int sy = MapIndex(py - r, Height);
                for (int px = 0; px < pw; px++)
                    p.Data[py * pw + px] = Data[sy * Width + MapIndex(px - r, Width)];
            });
            return p;
        }
    }
}