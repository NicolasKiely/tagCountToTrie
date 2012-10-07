/* Header file for defining Trie nodes and leafs, as well as
	generic operations on them.
*/

#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>


/* Trie Node */
struct TrieNode {
  struct TrieNode *a;
  struct TrieNode *t;
  struct TrieNode *g;
  struct TrieNode *c;
  
  struct TrieLeaf *pLeaf;
};


/* Trie leaf data */
struct TrieLeaf {
  int index;

  int tagLength;

  int tagFreq;
};


/* Used for calculating size of trie */
struct TrieStat {
	/* Total amount of memory used */
	int totalSize;
	
	/* Memory used by nodes */
	int nodeSize;
	
	/* Number of nodes used, not counting root */
	int usedNodes;
	
	/* Number of nodes used and unused, not counting root */
	int totalNodes;
	
	/* Memory used for leaves */
	int leafSize;
	
	/* Leaf nodes used */
	int usedLeaves;
	
	/* Total number of leaves */
	int totalLeaves;
};


/* Returns a newly created trie node */
struct TrieNode *initNode();

/* Checks to see if a node has a child node of character c.
   If found, returns that node, otherwise returns a newly created
   node for the character.
*/
struct TrieNode *add(struct TrieNode *pNode, char c);

/* Recursively frees a trie. Will set the pointer to null */
void freeTrie(struct TrieNode **ppRoot);

/* Returns the memory usage of a trie sturcture */
struct TrieStat getMemStat(struct TrieNode *pRoot);

/* Recursively calculates node's and child nodes' memory stats */
void calcMemStat(struct TrieNode *pNode, struct TrieStat *pStat);

#endif
