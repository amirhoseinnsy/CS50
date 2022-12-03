#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long number = get_long("Number: ");
    long i = number;
    long odd_even = 0;
    long sumeven = 0;
    long sumodd = 0;
    long total = 0;

    while (i >= 1)
    {
        i /= 10;
        odd_even ++;
    }
    
    i = number;

    if (odd_even % 2 == 0)
    {
        while (i >= 1)
        {
            sumodd += (i % 10);
            i /= 100;
        }
        i = number;
        i /= 10;
        while (i >= 1)
        {
            long p = (i % 10) * 2;
            if (p / 10 < 1)
            {
                sumeven += p;
            }
            
            else
            {
                sumeven += (p % 10);
                p /= 10;
                sumeven += p;
            }
            i /= 100;
        }

    }
    else
    {
        while (i >= 1)
        {
            long p = (i % 10) * 2;
            if (p / 10 < 1)
            {
                sumeven += p;
            }
            else
            {
                sumeven += (p % 10);
                p /= 10;
                sumeven += p;
            }
            i /= 100;
        }
        i = number;
        i /= 10;
        while (i >= 1)
        {
            sumodd += i % 10;
            i /= 100;
        }
    }

    total += (sumeven + sumodd);
    if (total % 10 == 0)
    {
        if (number / 1000000000000000 > 0)
        {
            if (number / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("MASTERCARD\n");
            }
        }
        else
        {
            if (number / 100000000000000 > 0)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("VISA\n");
            }
        }
    }
    else 
    {
        printf("INVALID\n");
    }

}
