#include <stdio.h>

#include "output.h"


void writeTrieToFile(FILE * fOut, struct TrieNode *pNode){
	int count = 0;
	
	if (pNode == NULL) return;
	
	/* Count up number of non-null nodes */
	if (pNode->a != NULL) count++;
	if (pNode->g != NULL) count++;
	if (pNode->c != NULL) count++;
	if (pNode->t != NULL) count++;
	
	if (count == 0){
		/* No further nodes to call */
		if (pNode->pLeaf == NULL) printf("Warning: leafless end node\n");
		writeLeafToFile(fOut, pNode->pLeaf);
		
	} else {
		if (pNode->pLeaf != NULL) printf("Warning: internal leaf found\n");
	
		/* Recursively run through child nodes */
		if (count > 1) fprintf(fOut, "\n(");
		
		if (pNode->a != NULL){
			fprintf(fOut, "A");
			writeTrieToFile(fOut, pNode->a);
		}
		
		if (pNode->c != NULL){
			fprintf(fOut, "C");
			writeTrieToFile(fOut, pNode->c);
		}
		
		if (pNode->g != NULL){
			fprintf(fOut, "G");
			writeTrieToFile(fOut, pNode->g);
		}
		
		if (pNode->t != NULL){
			fprintf(fOut, "T");
			writeTrieToFile(fOut, pNode->t);
		}
		
		if (count > 1) fprintf(fOut, ")\n");
	}
}


void writeLeafToFile(FILE *fOut, struct TrieLeaf *pLeaf){
	if (pLeaf == NULL) return;
	fprintf(fOut, "[%i,%i,%i]",
		pLeaf->index, pLeaf->tagLength, pLeaf->tagFreq);
}