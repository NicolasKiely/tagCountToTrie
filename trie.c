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


struct TrieStat getMemStat(struct TrieNode *pRoot){
	struct TrieStat stat;
	
	/* Initialize stats */
	stat.totalSize   = 0;
	stat.nodeSize    = 0;
	stat.usedNodes   = 0;
	stat.totalNodes  = 0;
	stat.leafSize    = 0;
	stat.usedLeaves  = 0;
	stat.totalLeaves = 0;
	
	/* Calculate */
	calcMemStat(pRoot, &stat);
	
	return stat;
}


void calcMemStat(struct TrieNode *pNode, struct TrieStat *pStat){
	/* Add node's own memory size to stats */
	pStat->totalSize += sizeof(*pNode);
	pStat->nodeSize += sizeof(*pNode);
	pStat->usedNodes += 1;
	pStat->totalNodes += 4;
	
	/* Add leaf stats */
	pStat->totalLeaves++;
	if (pNode->pLeaf != NULL){
		pStat->totalSize += sizeof(*pNode->pLeaf);
		pStat->leafSize += sizeof(*pNode->pLeaf);
		pStat->usedLeaves++;
	}
	
	/* Add child node stats */
	if (pNode->a != NULL) calcMemStat(pNode->a, pStat);
	if (pNode->t != NULL) calcMemStat(pNode->t, pStat);
	if (pNode->g != NULL) calcMemStat(pNode->g, pStat);
	if (pNode->c != NULL) calcMemStat(pNode->c, pStat);
}