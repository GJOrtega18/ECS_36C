#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int min) {
    if (value < min) {
        leftSibling->insert(value);
    }
    else {
        int pos;
        for (pos = 0; pos < count && value > values[pos]; pos++) {
            values[pos] = values[pos+1];
        }
        values[pos-1] = value;
        leftSibling->insert(min);
    }
} // takes current min and compares to value inserted, then adds the smaller value to the leftSibling

void LeafNode::addToRight(int value, int max) {
    if (value > max) {
        rightSibling->insert(value);
    }
    else {
        // shift stuff up and put value in the correct place
        int pos;
        for (pos = count; pos != 0 && value < values[pos-1]; pos--) {
            values[pos] = values[pos - 1];
        }
        values[pos] = value;
        rightSibling->insert(max);
    }
} // takes current max and compares to value inserted, then adds the larger value to the rightSibling

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

void LeafNode::split(LeafNode* newNode, int value, int max) {
    // put value in the correct location
    if (max > value) {
        int pos;
        for (pos = count; pos != 0 && value < values[pos-1]; pos--) {
            values[pos] = values[pos - 1];
        }
        values[pos] = value;
    }

    // move half of the values to the new node
    for (int pos = (leafSize+1)/2; pos < leafSize; pos++) {
        newNode->insert(values[pos]);
        count--;
    }
    // insert the max into the new node
    newNode->insert((max > value)? max : value);

} // LeafNode::split()

LeafNode* LeafNode::insert(int value) {
    // get maximum and minimum
    int max = values[count-1];
    int min = getMinimum();

    // if the leaf has space for the value
    if (count < leafSize) {
        int pos;
        for (pos = count; pos != 0 && value < values[pos-1]; pos--) {
          values[pos] = values[pos - 1];
        }
        values[pos] = value;
        count++;
        // update minimums if parent exists
        if (parent && getMinimum() != min) { parent->updateMinimums(); }
    }
    // otherwise, it doesn't have enough space
    else {

        // look left
        if (leftSibling && leftSibling->getCount() < leafSize) { // does leftSibling exist and have space?

            addToLeft(value, min);
            // update minimum of parent if necessary
            if (parent && getMinimum() != min) {parent->updateMinimums(); }
        }
        // look right
        else if (rightSibling && rightSibling->getCount() < leafSize) { // does rightSibling exist and have space?

            addToRight(value, max);

        }
        // split
        else {
            // create new node on the right
            LeafNode* newNode = new LeafNode(leafSize, parent, this, rightSibling);
            // check if right sibling exists, reassign sibling pointer
            if (rightSibling) { rightSibling->setLeftSibling(newNode); }
            // reassign sibling pointer of this node
            rightSibling = newNode;

            split(newNode, value, max);

            // update minimums if parent exists
            if (parent && getMinimum() != min) { parent->updateMinimums(); }

            return newNode;
        }
    }
  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
    cout << "Leaf: ";
    for (int i = 0; i < count; i++)
        cout << values[i] << ' ';
    cout << endl;
}


// LeafNode::print()


