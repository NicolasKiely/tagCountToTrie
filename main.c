/* The object of this program is to take text based tag count files and 
   generate a trie. The idea is to see comparative memory usage */

#include <stdio.h>
#include <stdlib.h>

#include "trie.h"
#include "loader.h"
#include "output.h"

/* Helper function to clean up main()'s input/output file handles */
void cleanFileHandles(FILE **in, FILE **out);

/* Display statistics */
void printStats(struct TrieStat *pStat);

/* Represents memory usage as Ymb Zkb Wbytes */
char *repMem(int mem);



/* Program usage:
   trie inputFile outputFile */
int main(int argc, char *argv[]){
	char *inNm  = NULL; /* Input file name */
	char *outNm = NULL; /* Output file name */
	int c       =    0; /* Generic input character */
	FILE *fIn   = NULL; /* Input file's handle */
	FILE *fOut  = NULL; /* Output file's handle */

	if (argc != 3) {
		/* Invalid number of arguments. Print usage and exit */
		printf("Error, invalid number of arguments\n");
		printf("Usage: %s [input file] [output file]\n", argv[0]);
		return 1;
	}

	/* Grab file names */
	inNm = argv[1];
	outNm = argv[2];

	/* Attempt to open files */
	fIn = fopen(inNm, "r");
	fOut = fopen(outNm, "w");
  
	if (fIn == NULL || fOut == NULL){
		cleanFileHandles(&fIn, &fOut);
		printf("Error: Unable to open input or output file\n");
		return 1;
	}

	/* Read first input line over to output file */
	while (-1){
		c = fgetc(fIn);
		if (c == EOF){
			printf("Nothing of importance in input file\n");
			cleanFileHandles(&fIn, &fOut);
			return 1;
		}

		if (c == '\n' || c == '\r'){
			/* End of first line */
			fprintf(fOut, "\n");
			break;
		}

		/* Copy over character */
		fprintf(fOut, "%c", c);
	}
  
	/* Load rest of input file into trie */
	struct TrieNode *pRoot = loadTagCountFile(fIn);
  
	if (pRoot == NULL){
		printf("Error, loading failed\n");
		return 1;
	}
	
	/* Output Trie */
	writeTrieToFile(fOut, pRoot);

	/* Calculate memory statistics */
	struct TrieStat stat = getMemStat(pRoot);
	
	/* Display stats */
	printStats(&stat);
	
	/* Done */
	cleanFileHandles(&fIn, &fOut);
	return 0;
}


void printStats(struct TrieStat *pStat){
	int   n_used_n = pStat->usedNodes;
	float n_used_p = ((float) pStat->usedNodes * 100)/pStat->totalNodes;
	int   n_unused_n = pStat->totalNodes - pStat->usedNodes;
	float n_unused_p = 100 - n_used_p;
	int   n_total = pStat->totalNodes;
	int   n_size_n = pStat->nodeSize;
	float n_size_p = ((float) pStat->nodeSize * 100)/pStat->totalSize;
	char *n_mem = repMem(n_size_n);
	
	int   l_used_n = pStat->usedLeaves;
	float l_used_p = ((float)  pStat->usedLeaves * 100)/pStat->totalLeaves;
	int   l_unused_n = pStat->totalLeaves - pStat->usedLeaves;
	float l_unused_p = 100 - l_used_p;
	int   l_total = pStat->totalLeaves;
	int   l_size_n = pStat->leafSize;
	float l_size_p = ((float) pStat->leafSize * 100)/pStat->totalSize;
	char *l_mem = repMem(l_size_n);
	
	int   totalSize = pStat->totalSize;
	char *totalMem = repMem(pStat->totalSize);

	printf("-----*-----*-----*-----*-----\n");
	/* Display Node statistics */
	printf("Node stats:\n");
	printf("\tUsed nodes  : %8i (%4.2f%%)\n", n_used_n, n_used_p);
	printf("\tUnused nodes: %8i (%4.2f%%)\n", n_unused_n, n_unused_p);
	printf("\tTotal nodes : %8i\n\n", n_total);
	printf("\tTotal bytes used: %8i (%4.2f%%)\n", n_size_n, n_size_p);
	printf("\tMemory usage    : %s\n\n", n_mem);
	free(n_mem);
	
	printf("-----\n");
	printf("Leaf stats:\n");
	printf("\tUsed leaves  : %8i (%4.2f%%)\n", l_used_n, l_used_p);
	printf("\tUnused leaves: %8i (%4.2f%%)\n", l_unused_n, l_unused_p);
	printf("\tTotal leaves : %8i\n\n", l_total);
	printf("\tTotal bytes used: %8i (%4.2f%%)\n", l_size_n, l_size_p);
	printf("\tMemory usage    : %s\n\n", l_mem);
	free(l_mem);
	
	printf("-----\n");
	printf("Total bytes used: %8i\n", totalSize);
	printf("Total memory usage: %s\n\n", totalMem);
	free(totalMem);
	
	printf("-----*-----*-----*-----*-----\n");
}


void cleanFileHandles(FILE **fIn, FILE **fOut){
  if (fIn != NULL){
    if (*fIn != NULL){
      fclose(*fIn);
      *fIn = NULL;
    }
  }

  if (fOut != NULL){
    if (*fOut != NULL){
      fclose(*fOut);
      *fOut = NULL;
    }
  }
}


char *repMem(int mem){
	int mb;
	int kb;
	int b;

	/* AAAm BBBk CCCb */
	char *buf = malloc(15);
	
	b = mem;
	mb = b / (1000*1000);
	b  = b - mb*(1000*1000);
	
	kb = b / 1000;
	b  = b - kb*1000;
	
	sprintf(buf, "%3im %3ik %3ib", mb, kb, b);
	
	return buf;
}