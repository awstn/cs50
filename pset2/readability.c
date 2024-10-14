#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int getLetters(string text);
int getWords(string text);
int getSentences(string text);
float colemanIndex(int letterCount, int wordCount, int sentenceCount);

int main(void)
{
    // Ask for text that will be analyzed
    string text = get_string("Text: ");

    // Find the amount of letters in the text
    int letterCount = getLetters(text);
    // Find the amount of words in the text
    int wordCount = getWords(text);
    // Find the amount of sentences in the text
    int sentenceCount = getSentences(text);
    // input the amounts into this Coleman-Liau formula.
    float getGrade = colemanIndex(letterCount, wordCount, sentenceCount);

    if (getGrade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (getGrade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) getGrade);
    }
}

int getLetters(string text)
{
    int letterCount = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        int asciiValue = toupper(text[i]);
        if (asciiValue >= 65 && asciiValue <= 91)
        {
            letterCount++;
        }
    }

    return letterCount;
}

int getWords(string text)
{
    int wordCount = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        if (isspace(text[i]))
        {
            wordCount++;
        }
    }

    return wordCount + 1;
}

int getSentences(string text)
{
    int sentenceCount = 0;
    for (int i = 0, textLength = strlen(text); i < textLength; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
    }

    return sentenceCount;
}

float colemanIndex(int letterCount, int wordCount, int sentenceCount)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    float averageWords = 100 * ((float) letterCount / wordCount);
    float averageSentences = 100 * ((float) sentenceCount / wordCount);
    float colemanIndex = (0.0588 * averageWords - 0.296 * averageSentences - 15.8);

    // Round up if needed
    if (colemanIndex < 1)
    {
        return colemanIndex;
    }

    float roundUp = round(colemanIndex);

    return roundUp;
}
