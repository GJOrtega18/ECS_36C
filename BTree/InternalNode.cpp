#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [internalSize];
} // InternalNode::InternalNode()


void InternalNode::addNodeToLeft(int orig_min, BTreeNode *min_child, int newNode_min, BTreeNode *newNode) {
    // shift stuff down and put value in the correct place
    if (orig_min < newNode_min) {
        int pos;
        for (pos = 0; pos < count && newNode_min > keys[pos]; pos++) {
            keys[pos] = keys[pos+1];
            children[pos] = children[pos+1];
        }
        keys[pos-1] = newNode_min;
        children[pos-1] = newNode;
        ((InternalNode*)leftSibling)->insert(min_child);
    }
    else {
        ((InternalNode*)leftSibling)->insert(newNode);
    }
}   // reorder node if necessary, add the min_node between the new one and orig_min


void InternalNode::addNodeToRight(int max, BTreeNode *max_child, int newNode_min, BTreeNode *newNode) {
    // shift stuff up and put value in the correct place
    if (max > newNode_min) {
        int pos;
        for (pos = count; pos != 0 && newNode_min < keys[pos-1]; pos--) {
            keys[pos] = keys[pos - 1];
            children[pos] = children[pos-1];
        }
        keys[pos] = newNode_min;
        children[pos] = newNode;
        ((InternalNode*)rightSibling)->insert(max_child);
    }
    else {
        ((InternalNode*)rightSibling)->insert(newNode);
    }
}   // reorder node if necessary, add the max_node between the new one and orig_max

int InternalNode::getMinimum()const
{
    if(count > 0)   // should always be the case
        return children[0]->getMinimum();
    else
        return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
    int pos;

    for (pos = count-1; pos != 0 && value < keys[pos]; pos--) { }
    BTreeNode* createdNode = children[pos]->insert(value);

    if (createdNode) {
        InternalNode* newNode = this->insert(createdNode);
        return newNode;
    }
    return NULL; // to avoid warnings for now.
} // InternalNode::insert()


InternalNode* InternalNode::insert(BTreeNode *newNode) // from a sibling or BTree::insert
{
    // students must write this
  
    // get maximum and minimum of keys and corresponding children
    int max = keys[count-1];
    BTreeNode* max_child = children[count-1];

    int newNode_min = newNode->getMinimum();
    int orig_min = getMinimum();
    BTreeNode* min_child = children[0];

    // if the node has space for the child
    if (count < internalSize) {
        int pos;
        for (pos = count; pos != 0 && newNode_min < keys[pos-1]; pos--) {
            keys[pos] = keys[pos - 1];
            children[pos] = children[pos-1];
        }
        keys[pos] = newNode_min;
        children[pos] = newNode;
        children[pos]->setParent(this);
        count++;
        // update minimums if parent exists
        if (parent && getMinimum() != orig_min) { parent->updateMinimums(); }
    }

    // otherwise, it doesn't have enough space
    else {

        // look left
        if (leftSibling && leftSibling->getCount() < internalSize) { // does leftSibling exist and have space?
            //leftSibling->insert(min_child);
            addNodeToLeft(orig_min, min_child, newNode_min, newNode);

            // update minimum of parent if necessary
            if (parent && getMinimum() != orig_min) { parent->updateMinimums(); }
        }
        // look right
        else if (rightSibling && rightSibling->getCount() < internalSize) { // does rightSibling exist and have space?
            //rightSibling->insert(max_child);
            addNodeToRight(max, max_child, newNode_min, newNode);

            // update minimum of parent if necessary
            if (parent && getMinimum() != orig_min) { parent->updateMinimums(); }

        }
        // split
        else {
            // create new node on the right
            InternalNode* splitNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);

            // check if right sibling exists, reassign sibling pointer
            if (rightSibling) { rightSibling->setLeftSibling(splitNode); }
            // reassign sibling pointer of this node
            rightSibling = splitNode;

            split(splitNode, newNode);

            // update minimums if parent exists
            if (parent && getMinimum() != orig_min) { parent->updateMinimums(); }

            return splitNode;
        }

    }
    return NULL;

} // InternalNode::insert()

InternalNode * InternalNode::split(InternalNode *newNode, BTreeNode *value)
{

    // find corresponding child for max key
    int value_key = value->getMinimum();
    int max_key = keys[count-1];
    BTreeNode* max_child = (max_key > value_key)? children[count-1] : value;

    // put value in the correct location (if its not the max)

    if (max_key > value_key) {
        int pos;
        for (pos = count; pos != 0 && value_key < keys[pos-1]; pos--) {
            keys[pos] = keys[pos-1];
            children[pos] = children[pos-1];
        }
        keys[pos] = value_key;
        children[pos] = value;
    }

    // move half of the values to the new node
    for (int pos = (internalSize+1)/2; pos < internalSize; pos++) {
        newNode->insert(children[pos]);
        count--;
    }
    // insert the max into the new node
    newNode->insert(max_child);

    return newNode;
} // InternalNode::split()


void InternalNode::print(Queue <BTreeNode*> &queue)
{
    int i;

    cout << "Internal: ";
    for (i = 0; i < count; i++)
        cout << keys[i] << ' ';
    cout << endl;

    for(i = 0; i < count; i++)
        queue.enqueue(children[i]);

} // InternalNode::print()


void InternalNode::updateMinimums()
{ // called by child with a new minimum
    for (int i = 0; i < count; i++) {
        keys[i] = children[i]->getMinimum();
    }
    if (parent) { parent->updateMinimums(); }
}

// InternalNode::updateMinimums


