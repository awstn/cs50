#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

bool inOrder(int length);
void printWinner(void);

int array[] = {5, 6, 100, 1000};

int main(void)
{
    printWinner();



}

void printWinner(void)
{
    if (inOrder(3))
        printf("Its in order!\n");

    else
        printf("It is not in order.\n");
}

bool inOrder(int length)
{
    if (length == 0)
        return true;

    if (array[length] > array[length - 1])
        return inOrder(length - 1);

    return false;

}
