/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TreeNode.h
 * Author: jiananzhao
 *
 * Created on November 23, 2016, 6:48 PM
 */

#ifndef _TREENODE_H
#define _TREENODE_H

#include "DBentry.h"

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class TreeNode {
private:
    DBentry* entryPtr;
    TreeNode* left;
    TreeNode* right;

public:
    // contructor that makes TreeNode that points to Dbentry object
    TreeNode(DBentry* _entryPtr);

    // finds node with max key (ie alphabetically last)
    string maximum();

    // removes node with name name
    void deleteNode(TreeNode*& Node, string name, bool &check);

    // the destructor
    ~TreeNode();

    // sets the left child of the TreeNode.
    void setLeft(TreeNode* newLeft);

    // sets the right child of the TreeNode
    void setRight(TreeNode* newRight);

    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;

    // gets the right child of the TreeNode
    TreeNode* getRight() const;

    // returns a pointer to the DBentry the TreeNode contains.
    DBentry* getEntry() const;
};

#endif