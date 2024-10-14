// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;

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
    // WAV file header will be 8 bit --> uint8_t

    // uint8_t header[HEADER_SIZE];
    uint8_t *header = malloc(HEADER_SIZE);
    if (header == NULL)
    {
        printf("Error reading .wav file");
        return 2;
    }

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
    free(header);

    // TODO: Read samples from input file and write updated data to output file
    // WAV audio sample will be 16 bit --> int16_t
    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
