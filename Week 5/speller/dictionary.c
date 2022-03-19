// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // an array of letters length 40
    struct node *next; // pointer to the next node
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 650; // 25 letters plus 1 for apostrophe

// Hash table
node *table[N];

// Counter for size
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the incoming word
    int hashed_n = hash(word);
    node *cursor = table[hashed_n];
    // access the linked list at the index of the hash table
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[0] == 39) // if the second char is '
    {
        return (tolower(word[0] - 'a')); // return 0 if the first is apostrophe
    }
    return (tolower(word[0]) - 96); // return 1 for a, 2 for b etc until 25 for z
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }
    // read each string from the file
    char word[LENGTH];
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        // create a node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            for (int i = 0; i < N; i++)
            {
                free(table[i]->next);
            }
            free(table);
            return 1;
        }
        strcpy(n->word, word);
        n->next = NULL;
        // hash the word to obtain an integer
        int hashed_n = hash(n->word);
        // insert the node corresponding to the integer (table[0] = "a")
        n->next = table[hashed_n];
        table[hashed_n] = n;
        counter++;
    }
    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i <= N; i++)
    {
        cursor = table[i];
        tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }

    }
    return true;
}
