#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Buffer to hold one block (512 bytes) of data
    uint8_t buffer[512];

    // Counts how many JPEGs we found so far (used for the file names)
    int count = 0;

    // The JPEG file we are currently writing to (NULL = no file open yet)
    FILE *img = NULL;

    // Name of the file: "###.jpg" is 7 characters + 1 for the NUL character = 8
    char filename[8];

    // While there's still a full block left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check if this block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it because a new one starts here
            if (img != NULL)
            {
                fclose(img);
            }

            // Create the file name: 000.jpg, 001.jpg, 002.jpg ...
            sprintf(filename, "%03i.jpg", count);

            // Open the new JPEG file for writing
            img = fopen(filename, "w");

            count++;
        }

        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
