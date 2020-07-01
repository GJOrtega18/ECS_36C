// Author: Sean Davis

#include "CheckerRunner.h"
#include "checker.h"
#include <iostream>
#include <cstring>

Checker::Checker(const DictionaryWord *words, int numWords) 
{
  for (int i = 0; i < 37; i++) {
    tries[i] = new Trie();
  }

  for (int i = 0; i < numWords; i++) {
    tries[(std::strlen(words[i].word)-1)]->insert(words[i].word);
  }

} // Checker()



/*
  takes in a word, a matchingWords array, and *count
  modifies matchingWords to hold all of the matching words
  modifies count to be the count of matching words
  word found --> count==1, matchingWords contains the word
  word not found --> count==(number of words with one letter difference), matchingWords contains all words with one letter different
 */

void Checker::findWord(const char *word, char matchingWords[100][MAX_LENGTH + 1], int *count)
{
  // reset everything
  int index = std::strlen(word)-1;
  tries[index]->count = 0;
  tries[index]->matchIndex = 0;

  std::strcpy(tries[index]->wordToFind, word);


  // word not in trie
  if ((tries[index]->findExactWord(tries[index]->root, 0)) == NULL) {
    tries[index]->findWithError(tries[index]->root, 0, 0);
    (*count) = tries[index]->count;
    for (int i = 0; i < tries[index]->count; i++) {
      std::memcpy(matchingWords[i], tries[index]->matches[i], (MAX_LENGTH+1) * sizeof(char));
    }
  }
  // word in the trie
  else {
    (*count) = 1;
    std::strcpy(matchingWords[0], word);
  }
}








