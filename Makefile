trie.exe: loader.o trie.o main.c
	gcc -Wall -o trie.exe main.c loader.o trie.o

loader.o: loader.c loader.h trie.h
	gcc -Wall -o loader.o -c loader.c

trie.o: trie.c trie.h
	gcc -Wall -o trie.o -c trie.c