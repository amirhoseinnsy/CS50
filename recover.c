#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLKSZ  512
#define MAXFN 1024

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");

    BYTE buffer[BLKSZ];     /* don't use MagicNumbers, use a constant */
    char FILENAME[MAXFN];
    int counter = 0; //to handle naming of file
    FILE *outptr = NULL; //file pointer where to write

    while (fread(buffer, BLKSZ, 1, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL) 
            {
                fclose(outptr);
                counter++;
            }
            sprintf(FILENAME, "%03d.jpg", counter);
            outptr = fopen(FILENAME, "wb");     
        }
        if (outptr != NULL)
        {
            fwrite(buffer, BLKSZ, 1, outptr);
        }
    }
    fclose(outptr);
    fclose(inptr);
}
