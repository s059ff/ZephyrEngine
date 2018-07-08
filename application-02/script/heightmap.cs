#include "common.csh"

using System.Drawing;

float[,] heightmap(string imagePath, int splitX, int splitY, float min, float max)
{
    float[,] heights = new float[splitY, splitX];
    using (Bitmap bitmap = new Bitmap(imagePath))
    {
        for (int i = 0; i < splitY; i++)
        {
            for (int j = 0; j < splitX; j++)
            {
                var pixel = bitmap.GetPixel(bitmap.Width * j / splitX, bitmap.Height * i / splitY);
                heights[i, j] = pixel.R / 255.0f * (max - min) + min;
            }
        }
    }
    return heights;
}
