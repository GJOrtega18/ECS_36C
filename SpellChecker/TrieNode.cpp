#include "TrieNode.h"
#include <iostream>
#include <cstring>



TrieNode::TrieNode(TrieNode* firstChild, TrieNode* nextSibling, char letter, const char* word) :
firstChild(firstChild), nextSibling(nextSibling), letter(letter) {
  strcpy(this->word, word);
}



void TrieNode::print() {
  TrieNode* node = this;
  if (node == NULL) { return; }

  while (node) {
    std::cout << node->word << "( " << node->letter << " ) " ;
    if (node->firstChild) { node->firstChild->print(); }
    node = node->nextSibling;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

