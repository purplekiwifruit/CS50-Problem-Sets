#include "helpers.h"
#include <math.h>
int getSepia(int originalRed, int originalGreen, int originalBlue, int type);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                (int) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed + 1) /
                3.0;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = getSepia(originalRed, originalGreen, originalBlue, 0);
            image[i][j].rgbtGreen = getSepia(originalRed, originalGreen, originalBlue, 1);
            image[i][j].rgbtBlue = getSepia(originalRed, originalGreen, originalBlue, 2);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int left = 0;
        int right = width - 1;

        while (left < right)
        {
            int tmpRed = image[i][left].rgbtRed;
            int tmpGreen = image[i][left].rgbtGreen;
            int tmpBlue = image[i][left].rgbtBlue;

            image[i][left].rgbtRed = image[i][right].rgbtRed;
            image[i][left].rgbtGreen = image[i][right].rgbtGreen;
            image[i][left].rgbtBlue = image[i][right].rgbtBlue;

            image[i][right].rgbtRed = tmpRed;
            image[i][right].rgbtGreen = tmpGreen;
            image[i][right].rgbtBlue = tmpBlue;

            left += 1;
            right -= 1;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Find average
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = copy[i][j].rgbtRed;
            int sumGreen = copy[i][j].rgbtGreen;
            int sumBlue = copy[i][j].rgbtBlue;

            float count = 1.0;

            if (j - 1 >= 0)
            {
                sumRed += copy[i][j - 1].rgbtRed;
                sumGreen += copy[i][j - 1].rgbtGreen;
                sumBlue += copy[i][j - 1].rgbtBlue;

                count += 1.0;
            }

            if (j + 1 < width)
            {

                sumRed += copy[i][j + 1].rgbtRed;
                sumGreen += copy[i][j + 1].rgbtGreen;
                sumBlue += copy[i][j + 1].rgbtBlue;
                count += 1.0;
            }

            if (i - 1 >= 0)
            {
                sumRed += copy[i - 1][j].rgbtRed;
                sumGreen += copy[i - 1][j].rgbtGreen;
                sumBlue += copy[i - 1][j].rgbtBlue;
                count += 1.0;

                if (j - 1 >= 0)
                {
                    sumRed += copy[i - 1][j - 1].rgbtRed;
                    sumGreen += copy[i - 1][j - 1].rgbtGreen;
                    sumBlue += copy[i - 1][j - 1].rgbtBlue;
                    count += 1.0;
                }

                if (j + 1 < width)
                {
                    sumRed += copy[i - 1][j + 1].rgbtRed;
                    sumGreen += copy[i - 1][j + 1].rgbtGreen;
                    sumBlue += copy[i - 1][j + 1].rgbtBlue;
                    count += 1.0;
                }
            }

            if (i + 1 < height)
            {
                sumRed += copy[i + 1][j].rgbtRed;
                sumGreen += copy[i + 1][j].rgbtGreen;
                sumBlue += copy[i + 1][j].rgbtBlue;
                count += 1.0;

                if (j - 1 >= 0)
                {
                    sumRed += copy[i + 1][j - 1].rgbtRed;
                    sumGreen += copy[i + 1][j - 1].rgbtGreen;
                    sumBlue += copy[i + 1][j - 1].rgbtBlue;
                    count += 1.0;
                }

                if (j + 1 < width)
                {
                    sumRed += copy[i + 1][j + 1].rgbtRed;
                    sumGreen += copy[i + 1][j + 1].rgbtGreen;
                    sumBlue += copy[i + 1][j + 1].rgbtBlue;
                    count += 1.0;
                }
            }

            image[i][j].rgbtRed = (int) round(sumRed / count);
            image[i][j].rgbtGreen = (int) round(sumGreen / count);
            image[i][j].rgbtBlue = (int) round(sumBlue / count);
        }
    }
}

int getSepia(int originalRed, int originalGreen, int originalBlue, int type)
{
    int sepia = 0;
    // type == 0: red
    if (type == 0)
    {
        sepia = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
    }
    else if (type == 1) // green
    {
        sepia = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
    }
    else if (type == 2) // blue
    {
        sepia = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
    }

    if (sepia >= 255)
    {
        return 255;
    }
    else
    {
        return sepia;
    }
}
