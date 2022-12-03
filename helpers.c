#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0 ; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
            float x = (tmp[i][j].rgbtBlue + tmp[i][j].rgbtGreen + tmp[i][j].rgbtRed) / 3.0;

            image[i][j].rgbtBlue = round(x);
            image[i][j].rgbtGreen = round(x);
            image[i][j].rgbtRed = round(x);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE q[height][width];
    for (int i = 0 ; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            q[i][j] = image[i][j];
            float Red = .393 * q[i][j].rgbtRed + .769 * q[i][j].rgbtGreen + .189 * q[i][j].rgbtBlue;
            int Reda = round(Red);
            float Green = .349 * q[i][j].rgbtRed + .686 * q[i][j].rgbtGreen + .168 * q[i][j].rgbtBlue;
            int Greena = round(Green);
            float Blue = .272 * q[i][j].rgbtRed + .534 * q[i][j].rgbtGreen + .131 * q[i][j].rgbtBlue;
            int Bluea = round(Blue);
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }
            image[i][j].rgbtRed = round(Red);
            image[i][j].rgbtGreen = round(Green);
            image[i][j].rgbtBlue = round(Blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int s = j + 1;
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (s)];
            image[i][width - (s)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 6);
                }
            }
            else if (i > 0 && i < height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i- 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i- 1][j].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 6);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i - 1][j].rgbtRed) / 9);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen+ original[i + 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen) / 9);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue) / 9);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 4);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) / 4);
                }
                else
                {
                    image[i][j].rgbtRed = round((original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6);
                }
            }
        }
    }
    return;
}
