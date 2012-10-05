/* Header for parsing (text) tag count files */

#ifndef LOADER_H
#define LOADER_H

#include "trie.h"

/* Takes the input file handle and generates a Trie from it */
struct TrieNode *loadTagCountFile(FILE *fIn);

/* Multiplies number by ten, then adds on parsed value of c */
void reverseIntegerParser(int *pNum, char c);


#endif