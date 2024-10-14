#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Create an array with the points associated to the letter.
// The letter will be found via index.
int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Reference functions
string allCaps(string input);
int getScore(string input);

int main(void)
{
    // create two inputs to get string
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // convert those inputs into uppercase and get scores of the player inputs
    string allCaps1 = allCaps(player1);
    string allCaps2 = allCaps(player2);

    int p1Score = getScore(allCaps1);
    int p2Score = getScore(allCaps2);

    // return which player has the higher score

    if (p1Score > p2Score)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (p2Score > p1Score)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    printf("Tie!\n");
    return 0;
}

// Create a function that will conver the string to uppercase
string allCaps (string input)
{
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        input[i] = toupper(input[i]);
    }

    return input;
}

// Create a function to get the score of the string
int getScore(string input)
{
    int score = 0;
    for (int i = 0, length = strlen(input); i < length; i++)
    {
        int point = 0;
        int asciiValue = input[i];
        // if asciiValue is not a letter, then assign it as 0.
        if (asciiValue >= 65)
        {
            point = points[asciiValue - 65];
        }

        score += point;
    }

    return score;
}
