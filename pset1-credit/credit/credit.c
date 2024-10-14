#include <cs50.h>
#include <stdio.h>

string checkStartingNumbers(long cardNumber);
string checkDigits(long cardNumber);
int getDigitLength(long cardNumber);

int main(void)
{
    long cardNumberInput = get_long("Number: ");
    printf("%s", checkDigits(cardNumberInput));
}

// function that iterates over the card number
string checkDigits(long cardNumber)
{
    // Check if digit length is valid
    if (getDigitLength(cardNumber) == 0)
    {
        return "INVALID\n";
    }
    // iterate over the card number and take out the last number through each iteration
    int count = 0;
    int oddSum = 0;
    int evenSum = 0;
    long cardNumberCopy = cardNumber;

    while (cardNumberCopy > 0)
    {
        // if count is odd, add that to odd sum count
        // if count is even, multiply by 2.
        count++;
        if (count % 2 == 0)
        {
            int evenIndex = (cardNumberCopy % 10) * 2;
            cardNumberCopy /= 10;
            // if its larger than 9, separate sum into digits and add
            if (evenIndex > 9)
            {
                int endSplit = evenIndex % 10;
                int frontSplit = evenIndex / 10;
                evenSum += endSplit + frontSplit;
            }
            else
            {
                evenSum += evenIndex;
            }
        }
        else
        {
            oddSum += cardNumberCopy % 10;
            cardNumberCopy /= 10;
        }
    }
    // Add up odd and even index sums
    int addedSum = oddSum + evenSum;

    if (addedSum % 10 == 0)
    {
        return checkStartingNumbers(cardNumber);
    }

    else
    {
        return "INVALID\n";
    }
}
// Function counts digit length:
int getDigitLength(long cardNumber)
{
    int count = 0;

    while (cardNumber >= 1)
    {
        cardNumber = cardNumber / 10;
        count++;
    }

    if (count == 16 || count == 15 || count == 13)
    {
        return count;
    }
    else
    {
        return 0;
    }

}
// Function looks at the digits and checks if it meets this criteria:
// AMEX STARTS with 34 or 37 AMEX is 15 digits
// MASTERCARD STARTS with 51,52,53,54, or 55 MASTERCARD is 16 digit
// VISA STARTS with 4 VISA is 13 and 16 digit
string checkStartingNumbers(long cardNumber)
{
    int count = 0;
    int length = getDigitLength(cardNumber);
    // Check if its VISA at index 13 or 16
    while (cardNumber > 0)
    {
        int atIndex = cardNumber % 10;
        cardNumber /= 10;
        count++;

        printf("Length: %i Count: %i Index: %i\n", length, count, atIndex);

        if ((count == 13 && length == 13 && atIndex == 4) || (count == 16 && length == 16 && atIndex == 4))
        {
            return "VISA\n";
        }
        else if ((length == 16 && count == 15 && (atIndex == 1 || atIndex == 2 || atIndex == 3 || atIndex == 4 ||atIndex == 5)))
        {
            atIndex = cardNumber % 10;
            cardNumber /= 10;
            if (atIndex == 5)
            {
                return "MASTERCARD\n";
            }
            if (atIndex == 4)
            {
                return "VISA\n";
            }

        }
        else if ((length == 15 && count == 14 && (atIndex == 4 || atIndex == 7)))
        {
            atIndex = cardNumber % 10;
            cardNumber /= 10;
            if (atIndex == 3)
            {
                return "AMEX\n";
            }
        }
    }
    return "INVALID\n";
}
