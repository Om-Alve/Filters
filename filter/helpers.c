#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating average of all rgb values
            int avg;
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Assigning the average values to r , g and b
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculating sepia colour by using given formulae
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // if the sepia colours are greater than maximum rgb values
            if (sepiaRed > 255)
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
            // Assigning the ccalculated sepia values to every pixel
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
        for (int j = 0; j < width / 2.0; j++)
        {
            // Reversing the order of pixels in each row by swapping
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int x, y, sumRed, sumBlue, sumGreen;
    float pixelcount;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copying the pixels from original image to temp
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRed = sumGreen = sumBlue = 0;
            pixelcount = 0;
            // Checking neighbouring pixels
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    x = i + k;
                    y = j + l;

                    // checking if pixel exists
                    if (x < 0 || x > (height - 1) || y < 0 || y > (width - 1))
                    {
                        continue;
                    }
                    // Finding total sum of rgb values of all neighbouring pixels
                    sumRed += image[x][y].rgbtRed;
                    sumGreen += image[x][y].rgbtGreen;
                    sumBlue += image[x][y].rgbtBlue;

                    pixelcount++;
                }
                // Calculating average of all rgb values
                temp[i][j].rgbtRed = round(sumRed / pixelcount);
                temp[i][j].rgbtGreen = round(sumGreen / pixelcount);
                temp[i][j].rgbtBlue = round(sumBlue / pixelcount);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copying the pixels from temp to the original image
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            temp[i][j]=image[i][j];
        }
    }
    int Gx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};

    //Looping through each pixel
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int redX=0;
            int blueX=0;
            int greenX=0;
            int redY=0;
            int blueY=0;
            int greenY=0;

            //looping through each pixel for neighbouring pixels
            for(int x=0;x<3;x++)
            {
                for(int y=0;y<3;y++)
                {
                    if(i-1 + x < 0 || i-1 + x > height - 1 || j- 1 + y< 0 || j -1 + y > width -1)
                    {
                            continue;
                    }
                        // Calculate Gx for each colour
                    redX = redX +(image[i - 1 + x][j- 1 +y].
                    rgbtRed*Gx[x][y]);
                    greenX= greenX +(image[i - 1 + x][j- 1 +y].
                    rgbtGreen*Gx[x][y]);
                    blueX=blueX +(image[i - 1 + x][j- 1 +y].
                    rgbtBlue*Gx[x][y]);

                    // Calculate Gy for each colour
                    redY=redY +(image[i - 1 + x][j- 1 +y].
                    rgbtRed*Gy[x][y]);
                    greenY= greenY +(image[i - 1 + x][j- 1 +y].
                    rgbtGreen*Gy[x][y]);
                    blueY=blueY +(image[i - 1 + x][j- 1 +y].
                    rgbtBlue*Gy[x][y]);

                    }
                }
                    // Calculate square root of Gx2 and Gy2
                    int red = round(sqrt((redX * redX) + (redY * redY)));
                    int green = round(sqrt((greenX*greenX) + (greenY*
                    greenY)));
                    int blue= round(sqrt((blueX *blueX) + (blueY*blueY)));
                    // Cap value at 255 if exceeded
                    if (red > 255)
                    {
                        red = 255;
                    }
                    if (green > 255)
                    {
                        green= 255;
                    }
                    if(blue > 255)
                    {
                        blue= 255;
                    }
                    temp[i][j].rgbtRed= red;
                    temp[i][j].rgbtBlue= blue;
                    temp[i][j].rgbtGreen= green;

             }
    }
    // copying pixels into the image
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            image[i][j].rgbtRed=temp[i][j].rgbtRed;
            image[i][j].rgbtGreen=temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue=temp[i][j].rgbtBlue;
        }
    }
    return;
}