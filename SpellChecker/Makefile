checker.out : checker.o CheckerRunner.o Trie.o TrieNode.o	
	g++ -ansi -Wall -g checker.o CheckerRunner.o Trie.o TrieNode.o -o checker.out  

checker.o : checker.cpp CheckerRunner.h checker.h 
	g++ -ansi -Wall -g -c checker.cpp 

CheckerRunner.o : CheckerRunner.cpp CheckerRunner.h checker.h CPUTimer.h 
	g++ -ansi -Wall -g -c CheckerRunner.cpp

Trie.o : Trie.h Trie.cpp TrieNode.h
	g++ -ansi -Wall -g -c Trie.cpp

TrieNode.o : TrieNode.cpp TrieNode.h 
	g++ -ansi -Wall -g -c TrieNode.cpp

clean : 
	rm -f checker.out checker.o  CheckerRunner.o Trie.o TrieNode.o  
