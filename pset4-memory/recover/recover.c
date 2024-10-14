#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define BLOCKSIZE 512
#define FILENAME_SIZE 8

FILE *createSRCFile(char* filename);
FILE *createDSTFile(int count);

int main(int argc, char *argv[])
{
    // Check if argument is exactly one
    if (argc != 2)
    {
        printf("./recover FILENAME");
        return 1;
    }

    char *filename = argv[1];
    FILE *cameraFile = createSRCFile(filename);
    if (cameraFile == NULL)
    {
        fclose(cameraFile);
        printf("File could not be opened");
        return 1;
    }

    BYTE buffer[BLOCKSIZE];
    int fileCount = 0;

    FILE *jpegFile = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCKSIZE, cameraFile) > 0)
    {
        // Read the first elements to check if it is the first four bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If it is not the first file. Close the file.
            if (fileCount > 0)
            {
                fclose(jpegFile);
            }
            // Create new destination file
            jpegFile = createDSTFile(fileCount);

            if (jpegFile == NULL)
            {
                fclose(jpegFile);
                printf("Error");
                return 2;
            }
            // write to file
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, jpegFile);
            fileCount++;

        }

        // Write to file if JPEG file is not NULL.
        else if (jpegFile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCKSIZE, jpegFile);
        }

    }

    // Close files
    fclose(jpegFile);
    fclose(cameraFile);

    return 0;
}

FILE *createSRCFile(char* filename)
{
    // Open Memory Card
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    return file;
}

FILE *createDSTFile(int count)
{
    char *outputJPEG = malloc(FILENAME_SIZE);
    sprintf(outputJPEG, "%03i.jpg", count);
    FILE *img = fopen(outputJPEG, "w");
    free(outputJPEG);

    if (img == NULL)
        return NULL;

    return img;
}
