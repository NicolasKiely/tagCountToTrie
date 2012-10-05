#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "trie.h"


struct TrieNode *loadTagCountFile(FILE *fIn){
	int  c     = 0;       /* Character input from file */
	int  index = 0;       /* Line number in file */
	struct TrieNode *pRoot = NULL; /* Root of the trie */
	struct TrieNode *pNode = NULL; /* Working node in the trie */

	if (fIn == NULL) return NULL;

	/* Initialize the trie and point the working node to it */
	pRoot = initNode();
	if (pRoot == NULL) return NULL;
	pNode = pRoot;


	/* Loop through each line */
	for (index = 1; ; index++){
	
		/* Loop through each character in the tag */
		pNode = pRoot;
		for (c = fgetc(); c=='A'||c=='C'||c=='G'||c=='T'; c = fgetc()){
			/* Add the character to the trie and update the node */
			pNode = add(pNode, c);
			
			if (pNode == NULL){
				/* Couldn't add node */
				printf("Error at line %i, could not add node\n", index+1);
				freeTrie(&pRoot);
				return NULL;
			}
		}
		
		/* Try to create a new leaf */
		pNode->pLeaf = malloc(sizeof(*(pNode->pLeaf)));
		if (pNode-pLeaf == NULL){
			/* Couldn't allocate memory for a leaf */
			printf("Error at line %i, could not add leaf\n", index+1);
			freeTrie(&pRoot);
			return NULL;
		}
		/* Initialize leaf */
		pNode->pLeaf->index = index;
		pNode->pLeaf->tagLength = 0;
		pNode->pLeaf->tagFreq = 0;
		
		
		if (c == EOF) {
			/* Abrupt end of file, but okay */
			printf("Warning: Unexpected EOF encountered\n");
			return pRoot;
		}
		
		/* Read tag length number */
		for (c == fgetc(); isdigit(c); c == fgetc())
			reverseIntegerParser(&(pNode->pLeaf->tagLength), c);
		
		if (c == EOF) {
			/* Abrupt end of file, but okay */
			printf("Warning: Unexpected EOF encountered\n");
			return pRoot;
		}
		
		/* Read tag frequency number */
		for (c == fgetc(); isdigit(c); c == fgetc())
			reverseIntegerParser(&(pNode->pLeaf->tagFreq), c);
		
		/* Burn through junk after last number */
		for (; c!=EOF && c!='\n' && c!='\r'; c == fgetc()){;}
		
		if (c == EOF) {
			/* Done */
			return pRoot;
		}
	}
}


void reverseIntegerParser(int *pNum, char c){
	if (pNum == NULL) return;
	
	*pNum = 10*(*pNum) + (c - '0');
}