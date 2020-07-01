#include <cstring>
#include <iostream>
#include "Trie.h"

Trie::Trie()
{
    root = NULL;
}

void Trie::insert(const char* word) {
    if (!root) {
      root = new TrieNode(NULL, NULL, word[0], word);
    }
    else {
      strcpy(wordParam, word);
      insert(root, 0);
    }
}

void Trie::insert(TrieNode* node, int pos) {

  // matches the letter --> go down
  if (wordParam[pos] == node->letter) {
    // if it has a child
    if (node->firstChild) {
      insert(node->firstChild, pos+1);
    }
    // if there is no child
    else {
      // make a new node with the current node's word and the next letter
      node->firstChild = new TrieNode(NULL, NULL, wordParam[pos+1], wordParam);

    }
  }

  // doesn't match the letter --> go right
  else {
    // if sibling exists
    if (node->nextSibling) {
      insert(node->nextSibling, pos);
    }
    // if sibling doesn't exist
    else {
      node->nextSibling = new TrieNode(NULL, NULL, wordParam[pos], wordParam);
    }
  }
}

void Trie::print()
{

    TrieNode* node = root;
    if (node == NULL) { return; }

    while (node) {
      std::cout << node->word << "(" << node->letter << ") " ;
      if (node->firstChild) { node->firstChild->print(); }
      node = node->nextSibling;
      std::cout << std::endl;
    }

}



char* Trie::findExactWord(TrieNode *node, int pos) {

    // if letter matches: go down
    if (node->letter == wordToFind[pos]) {
        if (std::strcmp(&(node->word[pos]), &(wordToFind[pos])) == 0) {
            return node->word;
        }
        //order: go down before you go right to traverse entire list
        else if (node->firstChild) {
            return findExactWord(node->firstChild, ++pos);
        }

    } // letter doesn't match: go right
    else {
        if (node->nextSibling) {
            return findExactWord(node->nextSibling, pos);
        }
    }
    return NULL;
}

bool Trie::hasOneDiff(const char* word1, const char* word2) {
  int errCount = 0;
  int i = 0;
  for (; word1[i] != '\0' && word2[i] != '\0'; i++) {
    if (word1[i] != word2[i]) { errCount++; }
  }
  // same length and at most one difference
  return (word1[i] == '\0') && (word2[i] == '\0') && (errCount <= 1);
}


void Trie::findWithError(TrieNode *node, int pos, int error) {

  if (error == 1) {

    // letter matches
    if (wordToFind[pos] == node->letter) {
      // check if rest of word matches
      if ((std::strcmp(&(node->word[pos+1]), &(wordToFind[pos+1])) == 0) && (strlen(node->word) == strlen(wordToFind))) {
        std::strcpy(matches[matchIndex++], node->word); // add current word to matches
        count++;
      }
      if (node->firstChild) { findWithError(node->firstChild, pos+1, error); }
      if (node->nextSibling) { findWithError(node->nextSibling, pos, error); }

    }
      // letter doesn't match
    else {
      // only check sibling, too many errors to check child
      if (node->nextSibling) { findWithError(node->nextSibling, pos, error); }
    }

  }

    // error == 0
  else {

    // letter matches
    if (wordToFind[pos] == node->letter) {
      // if rest of word matches
      if ((std::strcmp(&(node->word[pos+1]), &(wordToFind[pos+1])) == 0 ) ||
          hasOneDiff(&(node->word[pos+1]), &(wordToFind[pos+1]))) {
        std::strcpy(matches[matchIndex++], node->word); // add current word to matches
        count++;
      }
      if (node->firstChild) { findWithError(node->firstChild, pos+1, error); }
      if (node->nextSibling) { findWithError(node->nextSibling, pos, error); }
    }
      // letter doesn't match
    else {
      // if rest of word matches
      if ((std::strcmp(&(node->word[pos+1]), &(wordToFind[pos+1])) == 0) && (strlen(node->word) == strlen(wordToFind))) {
        std::strcpy(matches[matchIndex++], node->word); // add current word to matches
        count++;
      }
      if (node->firstChild) { findWithError(node->firstChild, pos+1, error+1); }
      if (node->nextSibling) { findWithError(node->nextSibling, pos, error); }
    }

  }
}
