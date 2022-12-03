// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int sum = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    
    node *tmp = table[index];

    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char temp = tolower(word[0]);
    int place = (temp - 97);
    return place;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char d_word[LENGTH + 1];
    for (int i = 0; i < N; i++) 
    {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r"); 

    if (file == NULL)
    {
        return false;
    }

    while (fscanf(file, "%s\n", d_word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(n->word, d_word);

        int index = hash(d_word);

        n->next = table[index];
        table[index] = n;
        sum++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (sum > 0)
    {
        return sum;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *pointer = table[i];

        while (pointer)
        {
            node *tmp = pointer;
            pointer = pointer->next;
            free(tmp);
        }
    }

    return true;
}
