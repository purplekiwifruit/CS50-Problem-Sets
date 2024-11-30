// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare a global variable to track word_count
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the hash_value of the word
    unsigned int hash_value = hash(word);

    node *curr = table[hash_value];

    while (curr != NULL)
    {
        if (strcasecmp(word, curr->word) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("The %s is unable to open", dictionary);
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    unsigned int hash_value;
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy each word to a node
        strcpy(n->word, word);
        // Get the Hash Value for each word
        hash_value = hash(word);
        // Insert the node into Hash Table according to the respective Hash Value
        n->next = table[hash_value];
        table[hash_value] = n;

        // tracking the number of words
        word_count++;
    }

    // Close the dictionary file
    fclose(file);
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
    // Iterate through the hash table
    for (int i = 0; i < N; i++)
    {
        node *curr = table[i];
        while (curr != NULL)
        {
            node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    return true;
}
