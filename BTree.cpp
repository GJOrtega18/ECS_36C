#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
  root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  // students must write this
  BTreeNode* newNode = root->insert(value);
  // if a new node has been created, and passed up, need to make an internal node
  if (newNode) {
    InternalNode* newInternal = new InternalNode(internalSize, leafSize, NULL, NULL, NULL);
    newInternal->insert(root);
    newInternal->insert(newNode);
    newNode->setParent(newInternal);
    root->setParent(newInternal);
    root = newInternal;
  }
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);

  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
