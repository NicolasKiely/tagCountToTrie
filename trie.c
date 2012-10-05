/* Source code for generic operations on a trie */
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
  pNode->pLeaf = NULL;

  return pNode;
}


struct TrieNode *add(struct TrieNode *pNode, char c){
  struct TrieNode **pNext;

  if (pNode == NULL) return NULL;

  /* Find child node */
  switch (c) {
  case 'A':
    pNext = &(pNode->a);
    break;

  case 'C':
    pNext = &(pNode->c);
    break;

  case 'G':
    pNext = &(pNode->g);
    break;

  case 'T':
    pNext = &(pNode->t);
    break;

  default:
    /* Error, nothing found */
    return NULL;
  }

  /* Check for untouched path in trie, create new one if not found */
  if (*pNext == NULL) *pNext = initNode();

  return *pNext;
}


void freeTrie(struct TrieNode **ppRoot){
  struct TrieNode *pRoot;
	
  if (ppRoot == NULL) return;
	
  /* Step pointer down */
  pRoot = *ppRoot;
  if (pRoot == NULL) return;
	
  /* Free child nodes */
  freeTrie(&(pRoot->a));
  freeTrie(&(pRoot->c));
  freeTrie(&(pRoot->g));
  freeTrie(&(pRoot->t));
	
  /* Free leaf */
  if (pRoot->pLeaf != NULL) free(pRoot->pLeaf);
	
  /* Reset original pointer */
  *ppRoot = NULL;
}