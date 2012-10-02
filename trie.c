#include <stdlib.h>

#include "trie.h"


struct TrieNode *initNode(){
  /* Attempt memory allocation */
  struct TrieNode *pNode = malloc(sizeof(*pNode));

  if (pNode == NULL) return NULL;

  /* Initialize fields */
  pNode->a = NULL;
  pNode->g = NULL;
  pNode->t = NULL;
  pNode->c = NULL;
  pNode->pField = NULL;

  return pNode;
}
