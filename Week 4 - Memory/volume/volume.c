// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];            // array of 44 bytes to hold the header
    fread(header, HEADER_SIZE, 1, input);   // read the header from the input file
    fwrite(header, HEADER_SIZE, 1, output); // write the same header to the output file

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // buffer to hold one 16-bit sample

    // fread returns the number of items read, so the loop stops at the end of the file
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Change the volume of the sample
        buffer *= factor;

        // Write the updated sample to the output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
