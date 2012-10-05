trie.exe: loader.o trie.o output.o main.c trie.h loader.h output.h
	gcc -Wall -o trie.exe main.c loader.o trie.o output.o

loader.o: loader.c loader.h trie.h
	gcc -Wall -o loader.o -c loader.c

trie.o: trie.c trie.h
	gcc -Wall -o trie.o -c trie.c

output.o: output.c output.h trie.h
	gcc -Wall -o output.o -c output.c