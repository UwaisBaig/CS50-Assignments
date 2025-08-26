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

// variable for counting words
int word_counter = 0;

// number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word to obtain a hash value
    int hash_value = hash(word);

    // creating the cursor to move through the file
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        // traverse linked list, looking for the word (strcasecmp)
        if (strcasecmp(cursor->word, word) == 0) // checks if their is the word
        {
            return true; // found the word
        }
        else
        {

            cursor = cursor->next; // check other word
        }
    }

    return false; // not found the word
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    for (int i = 0; i < N; i++) // making sure if the table doesnt has garbage value
    {
        table[i] = NULL;
    }

    FILE *dictionary_file = fopen(dictionary, "r"); // openiing dictionary file
    if (dictionary_file == NULL)
    {
        printf("Error while opening file \n");
        return false;
    }

    char buffer[LENGTH]; // creating buffer as temp var

    while (fscanf(dictionary_file, "%s", buffer) != EOF)
    {
        node *word_new = malloc(sizeof(node));

        // hash word to obtain hash value
        int hash_value = hash(buffer);

        // inset node into hash table at that location
        strcpy(word_new->word, buffer);
        word_new->next = table[hash_value];
        table[hash_value] = word_new;

        word_counter++; // incrementing word counter
    }

    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *temp = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
