#include <stdio.h>
#include <cs50.h>

#define LENGTH 6

void selectionSort(int array[], int length);

int main(void)
{
    int array1[] = {5, 2, 1, 6, 3, 4};
    selectionSort(array1, LENGTH);



}

void selectionSort(int array[], int length)
{
    int counter = 1;
    for (int x = 0; x < length; x++)
    {
        int greatest = array[x];
        int greatestIndex = x;
        for (int y = counter; y < length; y++)
        {
            if (greatest < array[y])
            {
                greatest = array[y];
                greatestIndex = y;
            }
        }
        array[greatestIndex] = array[x];
        array[x] = greatest;
        counter++;

    }

    for (int i = 0; i < LENGTH; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");

}
