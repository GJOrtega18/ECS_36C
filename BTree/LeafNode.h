#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  void addToLeft(int value, int min);
  void addToRight(int value, int max);
  int getMinimum() const;  // called by parent
  void split(LeafNode* newNode, int value, int max);
  LeafNode* insert(int value); // called by parent, sibling, or BTree::insert()
    // Returns pointer to new Leaf if it splits else NULL
  void print(Queue <BTreeNode*> &queue);
}; //LeafNode class

#endif
