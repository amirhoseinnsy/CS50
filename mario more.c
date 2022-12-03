#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    // getting height
    int height = get_int("Height: ");
    if (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    // printing hashtags
    for (int i = 0; i < height; i++)
    {
        for (int g = height - 1; g > i; g--)
        {
            printf(" ");
        }
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
