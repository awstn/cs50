#include <cs50.h>
#include <stdio.h>

int changeCount(int change);

int main(void)
{
    // Ask user for change owed
    int changeOwed = get_int("Change owed: ");
    printf("%i\n", changeCount(changeOwed));

}

int changeCount(int change)
{
    // Set coin counter
    int coinCounter = 0;

    while (change != 0)
    {
    // Check if Quarter can be dispensed
    // if so subtract quarter value from change owed and add to changeCounter
        while (change - 25 >= 0)
        {
            change -= 25;
            coinCounter++;
        }
    // Chcek if Dime can be dispensed
    // if so subtract Dime value from change owed
        while (change - 10 >= 0)
        {
            change -= 10;
            coinCounter++;
        }
    // Check if Nickle can be dispensed
    // if so subtract nickle value from change owed
        while (change - 5 >= 0)
        {
            change -= 5;
            coinCounter++;
        }
    // Check if Penny can be dispensed
    // if so subtract penny value from change owed
        while (change - 1 >= 0)
        {
            change -= 1;
            coinCounter++;
        }
    // Return the amount of coins used.
    }

    return coinCounter;
}
