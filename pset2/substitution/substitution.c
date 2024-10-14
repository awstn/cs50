#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool checkKey(string key);
void encypherText(string text, string key);

int main(int argc, string argv[])
{
    // Check if argc has two arguments is valid
    if (argc != 2)
    {
        printf("./substiution key\n");
        return 1;
    }
    if (!checkKey(argv[1]))
    {
        return 1;
    }

    printf("Passed!\n");

    // Get the plain text
    string inputText = get_string("plaintext: ");
    // Encypher the text and  Print the ciphertext
    printf("ciphertext: ");
    encypherText(inputText, argv[1]);
}

// Check the key to see if it meets the correct criteria:
bool checkKey(string key)
{
    int length = strlen(key);
    bool checkKey[26] = {false};

    // Check if it is 26 character length
    if (length != 26)
    {
        printf("Key must contain 26 characters\n");
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        // Check if all characters are in the alphabet.
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters\n");
            return false;
        }
        int index = key[i];
        if (isupper(index))
        {
            index -= 65;
        }
        if (islower(index))
        {
            index -= 97;
        }
        // Check if all characters are repeated only once.
        if (checkKey[index] == true)
        {
            printf("Key contains multiple of the same character\n");
            return false;
        }
        checkKey[index] = true;
    }

    return true;
}

void encypherText(string text, string key)
{
    int cypherArray[26];
    // Add to cypher array, the integers to encypher the message
    for (int i = 0, length = strlen(key); i < length; i++)
    {
        cypherArray[i] = key[i];
    }
    // Encypher the text using the cypher array
    string encypherText = "";
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        int index = text[i];
        if (isupper(text[i]))
        {
            index -= 65;
        }
        else
        {
            index -= 97;
        }

        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else if (islower(text[i]))
        {
            printf("%c", tolower(cypherArray[index]));
        }
        else
        {
            printf("%c", toupper(cypherArray[index]));
        }
    }
    printf("\n");
}
