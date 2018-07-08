using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using ZephyrSharp.Graphics;

public static class Texture2DExtensions
{
    public static void Print(this Texture2D @this, System.Drawing.Font font, string text)
    {
        var dummy = new Bitmap(1, 1);
        var size = Graphics.FromImage(dummy).MeasureString(text, font);
        var width = (int)size.Width;
        var height = (int)size.Height;
        var canvas = new Bitmap(width, height, PixelFormat.Format32bppArgb);
        var graphics = Graphics.FromImage(canvas);
        graphics.FillRectangle(Brushes.Transparent, new Rectangle(0, 0, canvas.Width, canvas.Height));
        graphics.DrawString(text, font, Brushes.White, 0, 0);
        using (var stream = new MemoryStream())
        {
            stream.Position = 0;
            canvas.Save(stream, ImageFormat.Bmp);
            byte[] buffer = new byte[stream.Length];
            stream.Position = 0;
            stream.Read(buffer, 0, (int)stream.Length);
            stream.Close();
            @this.Create(buffer, width, height, Format.UByte4NormBGRA, Accessibility.None);
        }
    }

    public static void Create(this Texture2D @this, Image image)
    {
        using (var ms = new MemoryStream())
        {
            image.Save(ms, ImageFormat.Bmp);
            @this.Create(ms.ToArray(), image.Width, image.Height, Format.UByte4NormBGRA, Accessibility.None);
        }
    }
}
