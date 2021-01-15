/****************************************************************************
 * dictionary.c
 *
 * CC50
 * Pset 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


// pointer to the beginning of the trie
node *first = NULL;
node *ptr = NULL;

// number of words in dictionary
unsigned int count;

/*
 * Returns true if word is in dictionary else false.
 */

bool
check(const char *word)
{
    // check pointer, pointed to the beginning of the trie
    node *checkptr = first;

    for (int i = 0; i < sizeof(word); i++)
    {
        // the boolean end is true in the last letter of the word, thus the word is in dictionary
        if (word[i] == '\0' && checkptr->end == true)
            return true;
        
        // the boolean end is false in the last letter of the word, thus the word is not in dictionary
        else if (word[i] == '\0' && checkptr->end == false)
            return false;

        // the pointer starts to point to the structure of the next letter
        else if (checkptr->letters[hash(word[i])] != NULL)
            checkptr = checkptr->letters[hash(word[i])];

         // the pointer of a letter of the word is NULL, that is, the word is not in the dictionary
        else if (checkptr->letters[hash(word[i])] == NULL)
            return false; 
    }

    return true;
}


/*
 * Converts a char to an unsigned int, based on the ASCII table and the alphabet.
 */

int
hash(int letter)
{
    int n;

    // converts upper case to a number from 1 to 26
    if (letter >= 65 && letter <= 90)
        n = letter - 64;

    // converts letter case to a number from 1 to 26
    else if (letter >= 97 && letter <= 122)
        n = letter - 96;

    // converts apostrophe to 27
    else if (letter == '\'')
        n = 0;

    return n;
}

/*
 * Loads dict into memory.  Returns true if successful else false.
 */

bool
load(const char *dict)
{
    // open the dictionary file
    FILE *infile = fopen(dict, "r");
    if (infile == NULL)
        return false;

    // pointer for the first node 
    first = calloc(28, sizeof(node));
    if (first == NULL)
        return false;

    //pointer to the nodes
    node *nextptr = first;

    // word storage variables
    int index = 0;
    char word[LENGTH+1];

    // stores the words of the file in the trie
    for (int c = fgetc(infile); c != EOF; c = fgetc(infile))
    {   
        // reads only letters and apostrophes
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == '\''))
        {
            word[index] = c;
            // checks if there is a struct for the char
            if (nextptr->letters[hash(word[index])] != NULL)
            {
                nextptr = nextptr->letters[hash(word[index])];
                index++;
            }

            // creates a new struct for the char
            else
            {
                nextptr->letters[hash(word[index])] = calloc(28, sizeof(node));
                if (nextptr->letters[hash(word[index])] == NULL)
                    return false;
                    
                nextptr = nextptr->letters[hash(word[index])];
                index++;
            }
        }

        // creates the last struct for a word
        else if (c == '\n')
        {
            // ends the word and stores the number of words
            word[index] = '\0';
            count++;

            // the boolean end is set to true, defining the end of the word
            nextptr->end = true;

            // prepares for a new word
            nextptr = first;
            index = 0;
        }
    }

    ptr = first;
    fclose(infile);
    return true;
}


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{
    return count;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool
unload(void)
{
    // array of 27 pointer to an node
    node *pointers[27] = {NULL};

    // defines where each pointer is pointed
    for (int i = 0; i < 27; i++)
        pointers[i] = ptr->letters[i];

    // free the allocated structure pointed by ptr
    free(ptr);

    // checks which structure pointers point to other structure, using recursion to free the following structures
    for (int j = 0; j < 27; j++)
    {
        if (pointers[j] != NULL)
        {
            ptr = pointers[j];
            unload();
        }
    }
    
    return true;
}
