#include <stdio.h>
#include <cs50.h>
#include <stdint.h>


int main (int argc, string argv[])
{
    // TODO: Check first four bytes in a given file
    string filename = argv[1];
    FILE *f = fopen(filename, "r");

    // Create a space where you will read those bytes (buffer)
    // uint8_t means: 8 means you want an integer that is 8 bits(1 byte) long, u means unsigned (or only positive), t meaans that is its only type.
    // regular integer is 4 bytes big
    uint8_t buffer[4];
    fread(buffer, 1, 4, f);

    for (int i = 0; i < 4; i++)
        printf("%i\n", buffer[i]);

    fclose(f);
}


