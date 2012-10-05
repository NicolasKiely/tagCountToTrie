/* Handles rendering a trie to a file */

#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>

#include "trie.h"

/* Recursively writes trie to file */
void writeTrieToFile(FILE *fOut, struct TrieNode *pNode);

/* Writes a leaf to a file */
void writeLeafToFile(FILE *fOut, struct TrieLeaf *pLeaf);

#endif