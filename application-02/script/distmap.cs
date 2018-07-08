#include "common.csh"

using System.Drawing;

float[,] distmap(string imagePath)
{
    float[,] probablities = null;
    using (Bitmap bitmap = new Bitmap(imagePath))
    {
        probablities = new float[bitmap.Height, bitmap.Width];
        for (int i = 0; i < bitmap.Height; i++)
        {
            for (int j = 0; j < bitmap.Width; j++)
            {
                var pixel = bitmap.GetPixel(j, i);
                probablities[i, j] = pixel.R / 255.0f;
            }
        }
    }
    return probablities;
}
