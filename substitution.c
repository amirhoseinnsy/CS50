#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, string argv[])
{
    //check to get rihgt key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int l = 0; l < strlen(argv[1]); l++)
    {
        if (isdigit(argv[1][l]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); i ++)
    {
        int repeat = 0;
        for (int l = 0; l < strlen(argv[1]); l++)
        {
            if (argv[1][i] == argv[1][l])
            {
                repeat ++;
            }
        }
        if (repeat > 1)
        {
            return 1;
        }
    }

    //get plaintext
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    // //shifting the letters
    for (int i = 0; i < strlen(text) ; i++)
    {
        if (islower(text[i]))
        {
            int new = (int)(text[i] - 97);
            char valu = tolower(argv[1][new]);
            printf("%c", valu);
        }
        else if (isupper(text[i]))
        {
            int new = (int)(text[i] - 65);
            char valu = toupper(argv[1][new]);
            printf("%c", valu);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;

}
