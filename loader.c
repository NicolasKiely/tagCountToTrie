#include <stdio.h>
#include <ctype.h>

#include "trie.h"


#define baseChr 1
#define sizeNum 2
#define freqNum 3


struct TrieNode *loadTagCountFile(FILE *fIn){
  int  c     = 0;       /* Character input from file */
  int  index = 1;       /* Line number in file */
  int  state = baseChr; /* Current State */
  char numBuff[6];      /* Buffer for storing numbers as strings */
  int  i     = 0;       /* Index of current working character for above */

  struct TrieNode *pRoot = NULL; /* Root of the trie */
  struct TrieNode *pNode = NULL; /* Working node in the trie */
  struct TrieLeaf *pLeaf = NULL; /* Working leaf in the trie */


  if (fIn == NULL) return NULL;

  /* Initialize the trie and point the working node to it */
  pRoot = initNode();
  if (pRoot == NULL) return NULL;
  pNode = pRoot;


  /* Loop through each character */
  while (-1){
    /* Grab current character */
    c = fgetc(fIn);

    if (state == baseChr) {
      if (c == 'A' || c == 'G' || c == 'C' || c == 'T'){
	/* Keep state, append character to trie ###!!!### */
	pNode = add(pNode, c);

	if (pNode == NULL) {

      } else if (c == '\t') {
	/* Move to number state */
	state = sizeNum;
	for (i = 0; i < 5; i++) numBuf[i] = '0';
	numBuf[5] = '\0';
	i = 0;

      } else if (c == EOF) {
	/* This may or may not be bad */
	printf("Unexcepected EOF reached\n");
	return pRoot;

      } else {
	printf("Unexpected character encountered\n");
      }

    } else if (state == sizeNum) {
      if (isnum(c)){
	/* Keep state, append number to buffer */
	
      }
    } else if (state == freqNum) {
    }
  }
}
