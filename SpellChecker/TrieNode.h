#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include "CheckerRunner.h"


class TrieNode {


    friend class Trie;

    public:
        TrieNode(TrieNode* firstChild, TrieNode* nextSibling, char letter, const char* word);
        void print();

    private:
        TrieNode* firstChild;
        TrieNode* nextSibling;
        char letter;
        char word[MAX_LENGTH + 1];

};


#endif
