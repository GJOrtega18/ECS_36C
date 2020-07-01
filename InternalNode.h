#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p, BTreeNode *left, 
    BTreeNode *right);
  void addNodeToLeft(int orig_min, BTreeNode* min_child, int newNode_min, BTreeNode* newNode);
  void addNodeToRight(int max, BTreeNode* max_child, int newNode_min, BTreeNode* newNode);
  int getMinimum()const;
  void updateMinimums(); // called by child with new minimum
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  InternalNode* insert(BTreeNode *newNode); // from a sibling or BTree::insert()
  InternalNode *split(InternalNode *newNode, BTreeNode *value);
  void print(Queue <BTreeNode*> &queue);
}; // InternalNode class

#endif
