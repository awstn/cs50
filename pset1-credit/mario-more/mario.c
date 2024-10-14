#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asking user for height of pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 9);

    // Making a counter variable to calculate the amount of whitespace printed
    int counter = 0;
    int hashCount = 0;

    // iterate through two loops
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // if the row plus the counter is less than the size of the pyramid, print a whitespace.
            if (i + counter < n - 1)
            {
                printf(" ");
                counter++;
            }
            else
            {
                printf("#");
                hashCount++;
            }
        }
        printf("  ");

        for (int x = 0; x < hashCount; x++)
        {
            printf("#");
        }

        hashCount = 0;
        counter = 0;
        printf("\n");
    }
}
