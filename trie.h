/* Header file for defining Trie nodes and leafs, as well as
	generic operations on them.
*/

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>


/* Trie Node */
struct TrieNode {
  struct Trie *a;
  struct Trie *t;
  struct Trie *g;
  struct Trie *c;
  
  struct TrieLeaf *pLeaf;
};


/* Trie leaf data */
struct TrieLeaf {
  int index;

  int tagLength;

  int tagFreq;
};


/* Returns a newly created trie node */
struct TrieNode *initNode();

/* Checks to see if a node has a child node of character c.
   If found, returns that node, otherwise returns a newly created
   node for the character.
*/
struct TrieNode *add(struct TrieNode *pNode, char c);

/* Recursively frees a trie. Will set the pointer to null */
void freeTrie(struct **TrieNode ppRoot);

#endif
