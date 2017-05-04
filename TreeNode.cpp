/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeNode.h"

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr; //points to Dbentry object
    left = NULL; //sets pointers to children to NULL
    right = NULL;
}

TreeNode::~TreeNode(){
    delete entryPtr; //deletes DBentry object that the TreeNode points to
}

void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

TreeNode* TreeNode::getLeft() const{
    return left;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

string TreeNode::maximum(){
    if (right == NULL) //if the right is NULL it is at the farthest right node
        return entryPtr->getName();
    else
        return right->maximum(); //otherwise go farther right
}

void TreeNode::deleteNode(TreeNode*& Node, string name, bool &check)
{
        if(name < Node->getEntry()->getName())
        {
            if(left != NULL)
            {
                (left->deleteNode(left, name, check));
            }
            return;
        }
        
        if(name > Node->getEntry()->getName())
        {
            if(right != NULL)
            {
                right->deleteNode(right, name, check);
            }
            return;
        }
        
        if((left == NULL)&&(right == NULL))//no nodes connected
        {
            Node = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else if((left == NULL)&&(right != NULL))//no right node connected
        {
            Node = right;
            right = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else if((left != NULL)&&(right == NULL))//no left node connected
        {
            Node = left;
            left = NULL;
            delete this;
            cout << "Success" << endl;
            check = true;
        }
        else//both left and right nodes connected
        {
            string max = left ->maximum();
            left->deleteNode(left, max, check);
            Node->getEntry()->setName(max);
            cout << "Success" << endl;
            check = true;
        }
}