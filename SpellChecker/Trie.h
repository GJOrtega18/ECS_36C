#ifndef TRIE_H
#define TRIE_H

//#include "CheckerRunner.h"
#include "TrieNode.h"

class TrieNode;

class Trie {

    friend class Checker;
    public:
        Trie();
//        char* findWithError(TrieNode *node, int pos, int error);
        void insert(const char* word);
        void print();


    private:

        void insert(TrieNode* node, int pos);
        TrieNode* root;
        char* findExactWord(TrieNode *node, int pos);
        void findWithError(TrieNode *node, int pos, int error);
        bool hasOneDiff(const char* word1, const char* word2);
        char count;
        char matches[100][MAX_LENGTH + 1];
        char wordParam[MAX_LENGTH + 1]; // stores the word so it doesn't need to be passed as a parameter
        char wordToFind[MAX_LENGTH + 1]; // stores word to find
        int matchIndex;


        

        


};


#endif
