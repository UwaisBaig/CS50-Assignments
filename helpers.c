#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0 ; i < height ; i++)
    {
        for(int j=0 ; j < width ; j++)
        {
           int red = image[i][j].rgbtRed;
           int green = image[i][j].rgbtGreen;
           int blue = image[i][j].rgbtBlue;

           int average = round(red+green+blue/3.0);

           image[i][j].rgbtRed = average;
           image[i][j].rgbtGreen = average;
           image[i][j].rgbtBlue = average;

        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0 ; i < height ; i++)
    {
        for (int j=0 ; j < width ; j++)
        {
            int OriginalRed = image[i][j].rgbtRed;
            int OriginalGreen = image[i][j].rgbtGreen;
            int OriginalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(0.393 * OriginalRed + 0.769 * OriginalGreen + 0.189 * OriginalBlue);
            int sepiaGreen = round(0.349 * OriginalRed + 0.686 * OriginalGreen + 0.168 * OriginalBlue);
            int sepiaBlue = round(0.272 * OriginalRed + 0.534 * OriginalGreen + 0.131 * OriginalBlue);


            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }


            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue  = sepiaBlue;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0 ; i < height ; i++)
    {
        for(int j=0 ; j < width/2 ; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 -j];

            image[i][width - 1 - j] = temp ;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy [height][width];


    for(int i = 0 ; i < height ; i++)
    {
        for(int j=0 ; j < width ; j++)
        {
            int totalred  = 0;
            int totalgreen = 0;
            int totalblue = 0;
            int count =0;

            for(int so_i = i-1 ; so_i <= i+1 ; so_i++)
            {
                for(int so_j = j-1 ; so_j <= j+1 ; so_j++)
                {

                    if(so_i >= 0 && so_i < height && so_j >=0 && so_j < width)
                    {
                        totalred += image[so_i][so_j].rgbtRed;
                        totalgreen += image[so_i][so_j].rgbtGreen;
                        totalblue += image[so_i][so_j].rgbtBlue;
                        count ++;
                    }

                }

            }

            copy[i][j].rgbtRed = round((float)totalred/count);
            copy[i][j].rgbtBlue = round((float)totalblue/count);
            copy[i][j].rgbtGreen = round((float)totalgreen/count);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

}
