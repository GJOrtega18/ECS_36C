#ifndef CHECKER_H
#define	CHECKER_H

#include "CheckerRunner.h"
#include "Trie.h"

class Checker {

public:
  Checker(const DictionaryWord *words, int numWords);
  void findWord(const char *word, char matchingWords[100][MAX_LENGTH + 1],
    int *count);

 private:

  Trie* tries[37];



}; // class Checker

#endif	// CHECKER_H

