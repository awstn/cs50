#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int factorial(int number);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("./factorial number");
    }
    int input = atoi(argv[1]);
    printf("%i\n", factorial(input));

}


int factorial(int number)
{
    // base case
    if (number == 1){
        return 1;
    }

    return number * factorial(number - 1);

}
