void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0 ; i < height; i++)
    {
        for (int j = 0; j < (width/2); j++)
        {
            int s = j + 1;

            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (s)];
            image[i][width - (s)] = temp;

        // int a = image[i][j].rgbtBlue;
        // int b = image[i][width - s].rgbtBlue;
        // swap(&a, &b);
        // int c = image[i][j].rgbtGreen;
        // int d = image[i][width - s].rgbtGreen;
        // swap(&c, &d);
        // int x = image[i][j].rgbtRed;
        // int y = image[i][width - s].rgbtRed;
        // swap(&x, &y);
        }
    }
    return;
}