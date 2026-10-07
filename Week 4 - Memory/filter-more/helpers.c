#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Go through every row
    for (int i = 0; i < height; i++)
    {
        // Go through every pixel in the row
        for (int j = 0; j < width; j++)
        {
            // Average of the three colors, rounded to the nearest integer
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Give the same value to all three colors so the pixel becomes gray
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only go through the left half, otherwise we would swap everything back
        for (int j = 0; j < width / 2; j++)
        {
            // Swap the pixel with its mirror on the other side of the row
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image, because we must read the ORIGINAL values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0; // how many neighbors are really inside the image

            // Look at the 3x3 box around the pixel (-1, 0, +1 rows and columns)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int row = i + di;
                    int col = j + dj;

                    // Skip neighbors that are outside the image
                    if (row < 0 || row >= height || col < 0 || col >= width)
                    {
                        continue;
                    }

                    sumRed += copy[row][col].rgbtRed;
                    sumGreen += copy[row][col].rgbtGreen;
                    sumBlue += copy[row][col].rgbtBlue;
                    count++;
                }
            }

            // Average of each color, rounded, saved in the real image
            image[i][j].rgbtRed = round(sumRed / (float) count);
            image[i][j].rgbtGreen = round(sumGreen / (float) count);
            image[i][j].rgbtBlue = round(sumBlue / (float) count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // The two Sobel kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sums for the x direction and the y direction, for each color
            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

            // Look at the 3x3 box around the pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int row = i + di;
                    int col = j + dj;

                    // Outside the image = black pixel (0), so it adds nothing. Skip it
                    if (row < 0 || row >= height || col < 0 || col >= width)
                    {
                        continue;
                    }

                    // di + 1 and dj + 1 turn -1..1 into 0..2 to use as kernel indexes
                    int kx = Gx[di + 1][dj + 1];
                    int ky = Gy[di + 1][dj + 1];

                    gxRed += copy[row][col].rgbtRed * kx;
                    gxGreen += copy[row][col].rgbtGreen * kx;
                    gxBlue += copy[row][col].rgbtBlue * kx;

                    gyRed += copy[row][col].rgbtRed * ky;
                    gyGreen += copy[row][col].rgbtGreen * ky;
                    gyBlue += copy[row][col].rgbtBlue * ky;
                }
            }

            // Combine Gx and Gy: square root of (Gx^2 + Gy^2), rounded
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            // A color value can't be more than 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}
