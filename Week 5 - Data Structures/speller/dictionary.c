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

// Number of buckets in the hash table (more buckets = shorter lists = faster check)
const unsigned int N = 100003;

// Hash table (global, so every bucket starts as NULL automatically)
node *table[N];

// Counts how many words we loaded
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find which bucket the word should be in
    unsigned int index = hash(word);

    // Walk through the linked list of that bucket
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        // strcasecmp compares two strings and ignores upper/lower case
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }

    // We went through the whole list and did not find the word
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int value = 0;

    // Go through every letter of the word
    for (int i = 0; word[i] != '\0'; i++)
    {
        // tolower makes the hash case-insensitive ("Foo" and "foo" give the same number)
        // Multiplying by 31 makes the order of the letters matter
        value = value * 31 + tolower(word[i]);
    }

    // % N keeps the number inside the table (from 0 to N - 1)
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Buffer to hold one word at a time
    char word[LENGTH + 1];

    // Read words one by one until there are no more words
    while (fscanf(source, "%s", word) == 1)
    {
        // Create space for a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Find which bucket this word belongs to
        unsigned int index = hash(word);

        // Put the new node at the START of the list of that bucket
        new_node->next = table[index];
        table[index] = new_node;

        // Count the word
        word_count++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go through every bucket
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Free every node in the list
        while (cursor != NULL)
        {
            // Save the current node, move to the next one, then free the saved one
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        table[i] = NULL;
    }

    return true;
}
