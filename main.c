/* The object of this program is to take text based tag count files and 
   generate a trie. The idea is to see comparative memory usage */

#include <stdio.h>

#include "trie.h"
#include "loader.h"
#include "output.h"

/* Helper function to clean up main()'s input/output file handles */
void cleanFileHandles(FILE **in, FILE **out);



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
  
	/* Done */
	cleanFileHandles(&fIn, &fOut);
	return 0;
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
