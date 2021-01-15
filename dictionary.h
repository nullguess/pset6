/****************************************************************************
 * dictionary.h
 *
 * CC50
 * Pset 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// struct that stores the words
typedef struct node
{
    bool end;
    struct node *letters[27];
} node;


/*
 * Returns true if word is in dictionary else false.
 */

bool check(const char *word);


/*
 * Converts a char to an unsigned int, based on the ASCII table and the alphabet.
 */

int hash(int letter);

/*
 * Loads dict into memory.  Returns true if successful else false.
 */

bool load(const char *dict);


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int size(void);


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool unload(void);


#endif // DICTIONARY_H
