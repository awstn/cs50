#include "helpers.h"
#include <math.h>
#include <stdio.h>

void swap (RGBTRIPLE *front, RGBTRIPLE *back);
void getAvgPixels(int targetX, int targetY, int height, int width,
                  RGBTRIPLE pixelCopy[height][width], RGBTRIPLE pixel[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE blueValue = image[i][j].rgbtBlue;
            BYTE redValue = image[i][j].rgbtRed;
            BYTE greenValue = image[i][j].rgbtGreen;

            BYTE avgValue = round((blueValue + redValue + greenValue) / 3.0);

            image[i][j].rgbtBlue = avgValue;
            image[i][j].rgbtRed = avgValue;
            image[i][j].rgbtGreen = avgValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE redValue = image[i][j].rgbtRed;
            BYTE greenValue = image[i][j].rgbtGreen;
            BYTE blueValue = image[i][j].rgbtBlue;

            double sepiaRed = round(.393 * redValue + .769 * greenValue + .189 * blueValue);
            double sepiaGreen = round(.349 * redValue + .686 * greenValue + .168 * blueValue);
            double sepiaBlue = round(.272 * redValue + .534 * greenValue + .131 * blueValue);

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int swapValue = width - j - 1;
            swap(&image[i][j], &image[i][swapValue]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            getAvgPixels(x, y, height, width, copy, image);
        }
    }
    return;
}

void swap(RGBTRIPLE *front, RGBTRIPLE *back)
{
    RGBTRIPLE temp = *front;
    *front = *back;
    *back = temp;
}

void getAvgPixels(int targetX, int targetY, int height, int width,
                  RGBTRIPLE pixelCopy[height][width], RGBTRIPLE pixel[height][width])
{
    int redValue = 0;
    int greenValue = 0;
    int blueValue = 0;
    double count = 0;

    for (int x = targetX - 1, boundryX = targetX + 1; x <= boundryX; x++)
    {
        // Check the height goes out of bounds
        if (x < 0 || x >= height)
            continue;

        for (int y = targetY - 1, boundryY = targetY + 1; y <= boundryY; y++)
        {
            // Check if the width goes out of bounds
            if (y < 0 || y >= width)
                continue;

            redValue += pixelCopy[x][y].rgbtRed;
            greenValue += pixelCopy[x][y].rgbtGreen;
            blueValue +=  pixelCopy[x][y].rgbtBlue;

            count++;
        }
    }

    pixel[targetX][targetY].rgbtRed = (BYTE) round(redValue / count);
    pixel[targetX][targetY].rgbtGreen = (BYTE) round(greenValue / count);
    pixel[targetX][targetY].rgbtBlue = (BYTE) round(blueValue / count);
}
