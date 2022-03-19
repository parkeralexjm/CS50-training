#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
        for (int j = 0, m = width; j < m; j++)
            {
                // find the average for rbg and then assign it to all the values
                int average = round(((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0));
                image[i][j].rgbtRed = average;
                image[i][j].rgbtBlue = average;
                image[i][j].rgbtGreen = average;
            }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
        for (int j = 0, m = width; j < m; j++)
            {
            // sepia algorithm to change the colour to the brown colour
            int red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // check if each value is over 255, otherwise set it to 255
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
            // set each value for RGB to the corrected sepia value or 255 if it was over 255
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
            }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, n = height; i < n; i++)
        for (int j = 0, m = width; j < m / 2; j++)
            {
                RGBTRIPLE tmp1 = image[i][m - 1 - j];
                image[i][m - 1 - j] = image[i][j];
                image[i][j] = tmp1;
                //BYTE tmp2 = *image[i][m - j].rgbtGreen;
                //*image[i][m - j].rgbtGreen = *image[i][j].rgbtGreen;
                //*image[i][j].rgbtGreen = tmp2;
                //BYTE tmp3 = *image[i][m - j].rgbtBlue;
                //*image[i][m - j].rgbtBlue = *image[i][j].rgbtBlue;
                //*image[i][j].rgbtBlue = tmp3;
            }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
RGBTRIPLE copy[height][width];
	float avgRed;
	float avgGreen;
	float avgBlue;

	//create a copy of original image to save original pixel values
	for (int row = 0; row < height; row++)
	{
		for (int w = 0; w < width; w++)
		{
			copy[row][w].rgbtRed = image[row][w].rgbtRed;
			copy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			copy[row][w].rgbtBlue = image[row][w].rgbtBlue;


		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			//if the pixel is on the top left edge
			if (w == 0 && h == 0)
			{
				avgRed = (float)(copy[h][w].rgbtRed + copy[h][w+1].rgbtRed + copy[h+1][w].rgbtRed + copy[h+1][w+1].rgbtRed) / 4;

				avgGreen = (float)(copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen + copy[h+1][w].rgbtGreen + copy[h+1][w+1].rgbtGreen) / 4;

				avgBlue = (float)(copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue + copy[h+1][w].rgbtBlue + copy[h+1][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgBlue = round(avgBlue);
				avgGreen = round(avgGreen);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on the lower left edge
			else if (w == 0 && h == (height - 1))
			{
				avgRed =(float)(copy[h-1][w].rgbtRed + copy[h-1][w+1].rgbtRed + copy[h][w].rgbtRed + copy[h][w+1].rgbtRed) / 4;

				avgGreen = (float)(copy[h-1][w].rgbtGreen + copy[h-1][w+1].rgbtGreen + copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen) / 4;

				avgBlue = (float)(copy[h-1][w].rgbtBlue + copy[h-1][w+1].rgbtBlue + copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue) / 4;
				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on top Right
			else if (h == 0 && w == (width - 1))
			{
				avgRed = (float)(copy[h][w-1].rgbtRed + copy[h][w].rgbtRed + copy[h+1][w-1].rgbtRed + copy[h+1][w].rgbtRed)/ 4;

				avgGreen = (float)(copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen + copy[h+1][w-1].rgbtGreen + copy[h+1][w].rgbtGreen) / 4;

				avgBlue = (float)(copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue + copy[h+1][w-1].rgbtBlue + copy[h+1][w].rgbtBlue) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}

			//if the pixel is on lower right
			else if(h == (height - 1) && w == (width - 1))
			{
				avgRed = (float)(copy[h-1][w-1].rgbtRed + copy[h-1][w].rgbtRed + copy[h][w-1].rgbtRed + copy[h][w].rgbtRed) / 4;

		 		avgBlue = (float)(copy[h-1][w-1].rgbtBlue + copy[h-1][w].rgbtBlue + copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue) / 4;

				avgGreen = (float)(copy[h-1][w-1].rgbtGreen + copy[h-1][w].rgbtGreen + copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen) / 4;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
                image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on left side

			else if (w == 0 && (h > 0 && h < height - 1))
			{
				avgRed = (float)(copy[h-1][w].rgbtRed + copy[h-1][w+1].rgbtRed + copy[h][w].rgbtRed + copy[h][w+1].rgbtRed + copy[h+1][w].rgbtRed + copy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(copy[h-1][w].rgbtGreen + copy[h-1][w+1].rgbtGreen + copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen + copy[h+1][w].rgbtGreen + copy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(copy[h-1][w].rgbtBlue + copy[h-1][w+1].rgbtBlue + copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue + copy[h+1][w].rgbtBlue + copy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on right side
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				avgRed = (float)(copy[h-1][w-1].rgbtRed + copy[h-1][w].rgbtRed + copy[h][w-1].rgbtRed + copy[h][w].rgbtRed + copy[h+1][w-1].rgbtRed + copy[h+1][w].rgbtRed) / 6;

				avgGreen = (float)(copy[h-1][w-1].rgbtGreen + copy[h-1][w].rgbtGreen + copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen + copy[h+1][w-1].rgbtGreen + copy[h+1][w].rgbtGreen) / 6;

				avgBlue = (float)(copy[h-1][w-1].rgbtBlue + copy[h-1][w].rgbtBlue + copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue + copy[h+1][w-1].rgbtBlue + copy[h+1][w].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
                                image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on upper side
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				avgRed = (float)(copy[h][w-1].rgbtRed + copy[h][w].rgbtRed + copy[h][w+1].rgbtRed + copy[h+1][w-1].rgbtRed + copy[h+1][w].rgbtRed + copy[h+1][w+1].rgbtRed) / 6;

				avgGreen = (float)(copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen + copy[h+1][w-1].rgbtGreen + copy[h+1][w].rgbtGreen + copy[h+1][w+1].rgbtGreen) / 6;

				avgBlue = (float)(copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue + copy[h+1][w-1].rgbtBlue + copy[h+1][w].rgbtBlue + copy[h+1][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
       //if the pixel is on lower side
			else if  (h == height - 1 && (w > 0 && w < width - 1))
			{
				avgRed = (float)(copy[h-1][w-1].rgbtRed + copy[h-1][w].rgbtRed + copy[h-1][w+1].rgbtRed + copy[h][w-1].rgbtRed + copy[h][w].rgbtRed + copy[h][w+1].rgbtRed) / 6;

				avgGreen = (float)(copy[h-1][w-1].rgbtGreen + copy[h-1][w].rgbtGreen + copy[h-1][w+1].rgbtGreen + copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen) / 6;
				avgBlue = (float)(copy[h-1][w-1].rgbtBlue + copy[h-1][w].rgbtBlue + copy[h-1][w+1].rgbtBlue + copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue) / 6;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}
      //if the pixel is on the middle and can form a 3x3 grid
			else
			{
				avgRed = (float)(copy[h-1][w-1].rgbtRed + copy[h-1][w].rgbtRed + copy[h-1][w+1].rgbtRed + copy[h][w-1].rgbtRed + copy[h][w].rgbtRed + copy[h][w+1].rgbtRed + copy[h+1][w-1].rgbtRed + copy[h+1][w].rgbtRed + copy[h+1][w+1].rgbtRed) / 9;
				avgGreen = (float)(copy[h-1][w-1].rgbtGreen + copy[h-1][w].rgbtGreen + copy[h-1][w+1].rgbtGreen + copy[h][w-1].rgbtGreen + copy[h][w].rgbtGreen + copy[h][w+1].rgbtGreen + copy[h+1][w-1].rgbtGreen + copy[h+1][w].rgbtGreen + copy[h+1][w+1].rgbtGreen) / 9;

				avgBlue = (float)(copy[h-1][w-1].rgbtBlue + copy[h-1][w].rgbtBlue + copy[h-1][w+1].rgbtBlue + copy[h][w-1].rgbtBlue + copy[h][w].rgbtBlue + copy[h][w+1].rgbtBlue + copy[h+1][w-1].rgbtBlue + copy[h+1][w].rgbtBlue + copy[h+1][w+1].rgbtBlue) / 9;

				avgRed = round(avgRed);
				avgGreen = round(avgGreen);
				avgBlue = round(avgBlue);

				image[h][w].rgbtRed = avgRed;
				image[h][w].rgbtGreen = avgGreen;
				image[h][w].rgbtBlue = avgBlue;
			}

		}
	}
    return;
}

                // RGBTRIPLE TL = copy[i - 1][j - 1];
                // RGBTRIPLE TM = copy[i - 1][j];
                // RGBTRIPLE TR = copy[i - 1][j + 1];
                // RGBTRIPLE ML = copy[i][j - 1];
                // RGBTRIPLE MM = copy[i][j];
                // RGBTRIPLE MR = copy[i][j + 1];
                // RGBTRIPLE BL = copy[i + 1][j + 1];
                // RGBTRIPLE BM = copy[i + 1][j];
                // RGBTRIPLE BR = copy[i + 1][j - 1];


                // if (i == 0 && j == 0)
                // {
                //     image[i][j].rgbtRed = ((MM.rgbtRed + MR.rgbtRed + BM.rgbtRed + BR.rgbtRed) / 4.0);
                //     image[i][j].rgbtGreen = ((MM.rgbtGreen + MR.rgbtGreen + BM.rgbtGreen + BR.rgbtGreen) / 4.0);
                //     image[i][j].rgbtBlue = ((MM.rgbtBlue + MR.rgbtBlue + BM.rgbtBlue + BR.rgbtBlue) / 4.0);

                // }
                // else if (i == 0)
                // {
                //     image[i][j].rgbtRed = round(((ML.rgbtRed + MM.rgbtRed + MR.rgbtRed + BL.rgbtRed + BM.rgbtRed + BR.rgbtRed) / 6.0));
                //     image[i][j].rgbtGreen = round(((ML.rgbtGreen + MM.rgbtGreen + MR.rgbtGreen + BL.rgbtGreen + BM.rgbtGreen + BR.rgbtGreen) / 6.0));
                //     image[i][j].rgbtBlue = round(((ML.rgbtBlue + MM.rgbtBlue + MR.rgbtBlue + BL.rgbtBlue + BM.rgbtBlue + BR.rgbtBlue) / 6.0));
                // }
                // else if (i == 0 && j == width - 1)
                // {
                //     image[i][j].rgbtRed = round(((ML.rgbtRed + MM.rgbtRed + BL.rgbtRed + BM.rgbtRed) / 4.0));
                //     image[i][j].rgbtGreen = round(((ML.rgbtGreen + MM.rgbtGreen + BL.rgbtGreen + BM.rgbtGreen) / 4.0));
                //     image[i][j].rgbtBlue = round(((ML.rgbtBlue + MM.rgbtBlue + BL.rgbtBlue + BM.rgbtBlue) / 4.0));

                // }
                // else if (j == width)
                // {
                //     image[i][j].rgbtRed = round(((TL.rgbtRed + TM.rgbtRed + ML.rgbtRed + MM.rgbtRed + BL.rgbtRed + BM.rgbtRed) / 6.0));
                //     image[i][j].rgbtGreen = round(((TL.rgbtGreen + TM.rgbtGreen + ML.rgbtGreen + MM.rgbtGreen + BL.rgbtGreen + BM.rgbtGreen) / 6.0));
                //     image[i][j].rgbtBlue = round(((TL.rgbtBlue + TM.rgbtBlue + ML.rgbtBlue + MM.rgbtBlue + BL.rgbtBlue + BM.rgbtBlue) / 6.0));

                // }
                // else if (i == height - 1 && j == width - 1)
                // {
                //     image[i][j].rgbtRed = round(((TL.rgbtRed + TM.rgbtRed + ML.rgbtRed + MM.rgbtRed) / 4.0));
                //     image[i][j].rgbtGreen = round(((TL.rgbtGreen + TM.rgbtGreen + ML.rgbtGreen + MM.rgbtGreen) / 4.0));
                //     image[i][j].rgbtBlue = round(((TL.rgbtBlue + TM.rgbtBlue + ML.rgbtBlue + MM.rgbtBlue) / 4.0));

                // }
                // else if (i == height - 1)
                // {
                //     image[i][j].rgbtRed = round(((TL.rgbtRed + TM.rgbtRed + TR.rgbtRed + ML.rgbtRed + MM.rgbtRed + MR.rgbtRed) / 6.0));
                //     image[i][j].rgbtGreen = round(((TL.rgbtGreen + TM.rgbtGreen + TR.rgbtGreen + ML.rgbtGreen + MM.rgbtGreen + MR.rgbtGreen) / 6.0));
                //     image[i][j].rgbtBlue = round(((TL.rgbtBlue + TM.rgbtBlue + TR.rgbtBlue + ML.rgbtBlue + MM.rgbtBlue + MR.rgbtBlue) / 6.0));

                // }
                // else if (i == height - 1 && j == 0)
                // {
                //     image[i][j].rgbtRed = round(((TM.rgbtRed + TR.rgbtRed + MM.rgbtRed + MR.rgbtRed) / 4.0));
                //     image[i][j].rgbtGreen = round(((TM.rgbtGreen + TR.rgbtGreen + MM.rgbtGreen + MR.rgbtGreen) / 4.0));
                //     image[i][j].rgbtBlue = round(((TM.rgbtBlue + TR.rgbtBlue + MM.rgbtBlue + MR.rgbtBlue) / 4.0));

                // }
                // else if (j == 0)
                // {
                //     image[i][j].rgbtRed = round(((TM.rgbtRed + TR.rgbtRed + MM.rgbtRed + MR.rgbtRed + BM.rgbtRed + BR.rgbtRed) / 6.0));
                //     image[i][j].rgbtGreen = round(((TM.rgbtGreen + TR.rgbtGreen + MM.rgbtGreen + MR.rgbtGreen + BM.rgbtGreen + BR.rgbtGreen) / 6.0));
                //     image[i][j].rgbtBlue = round(((TM.rgbtBlue + TR.rgbtBlue + MM.rgbtBlue + MR.rgbtBlue + BM.rgbtBlue + BR.rgbtBlue) / 6.0));

                // }
                // else
                // {
                //     image[i][j].rgbtRed = round(((TL.rgbtRed + TM.rgbtRed + TR.rgbtRed + ML.rgbtRed + MM.rgbtRed + MR.rgbtRed + BL.rgbtRed + BM.rgbtRed + BR.rgbtRed) / 9.0));
                //     image[i][j].rgbtGreen = round(((TL.rgbtGreen + TM.rgbtGreen + TR.rgbtGreen + ML.rgbtGreen + MM.rgbtGreen + MR.rgbtGreen + BL.rgbtGreen + BM.rgbtGreen + BR.rgbtGreen) / 9.0));
                //     image[i][j].rgbtBlue = round(((TL.rgbtBlue + TM.rgbtBlue + TR.rgbtBlue + ML.rgbtBlue + MM.rgbtBlue + MR.rgbtBlue + BL.rgbtBlue + BM.rgbtBlue + BR.rgbtBlue) / 9.0));

                // }