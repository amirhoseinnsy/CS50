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
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int l = 0; l < strlen(argv[1]); l++)
    {
        if (isalpha(argv[1][l]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //get plaintext
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    int key = (atoi(argv[1])) % 26;

    //shifting the letters
    for (int i = 0; i < strlen(text) ; i++)
    {
        if (islower(text[i]))
        {
            char new = text[i] - 97;
            new = (new + key) % 26;
            new += 97;
            printf("%c", new);
        }
        else if (isupper(text[i]))
        {
            char new = text[i] - 65;
            new = (new + key) % 26;
            new += 65;
            printf("%c", new);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;

}
