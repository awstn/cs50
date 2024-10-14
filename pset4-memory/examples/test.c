#include <stdio.h>
#include <cs50.h>


int main(void)
{

    char *s = "hi";
    int array[5] = {10, 15, 25, 35, 40};

    printf("%c\n", *s); // h
    printf("%s\n", s); // hi

    printf("%i\n", *array); // 10
    printf("%i\n", *(array + 1)); // 15
    printf("%i\n", *(array + 2)); // 25
    printf("%i\n", *(array + 3)); // 35

    
}



