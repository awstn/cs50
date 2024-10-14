// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;
int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int getHashCode = hash(word);
    node *ptr = table[getHashCode];

    // Check if location on Array is NULL.
    if (ptr == NULL)
        return false;

    // Iterate through linkedlist and find if word is the same.
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[1] == '\0')
        return (toupper(word[0]) * toupper(word[0])) % 100;
    else if (word[2] == '\0')
        return ((toupper(word[0])) * toupper(word[1]) % 100);
    else
        return ((toupper(word[0]) * toupper(word[1]) * toupper(word[2])) % 100);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fp = fopen(dictionary, "r");

    if (fp == NULL)
        return false;

    char wordToBeAdded[LENGTH];

    // Iterate over file and add word to buffer.
    while (fscanf(fp, "%s", wordToBeAdded) != EOF)
    {
        // Get hash code
        int getHashCode = hash(wordToBeAdded);
        // I have to use a double header, since head is creating a copy of table[getHashCode].
        // Using a pointer will access that data out of scope.
        node **head = &table[getHashCode];

        // Create new node that will be added to Hash Table
        node *n = malloc(sizeof(node));
        strcpy(n->word, wordToBeAdded);
        n->next = *head;
        *head = n;
        wordCount++;
    }

    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            ptr = table[i]->next;
            free(table[i]);
            table[i] = ptr;
        }
    }
    return true;
}
