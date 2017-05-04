/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TreeDB.h"

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB(){
    clear(); //calls clear to destroy all TreeNode objects
}

bool TreeDB::insert(DBentry* newEntry){
    if (root == NULL){ //if the tree is empty make head point to new node
        TreeNode *ins = new TreeNode (newEntry);
        root = ins;
        return true;
    }
    // Private helper function for recursion
    return insertHelper(newEntry, root);
}

bool TreeDB::insertHelper(DBentry* newEntry, TreeNode* cur){
    if (newEntry->getName() == cur->getEntry()->getName()){
        delete newEntry; // Not inserting in tree; must delete now
        return false; // No repeat insertions
    }
    if (newEntry->getName() < cur->getEntry()->getName()){ // Go left
        if (cur->getLeft() == NULL){
            TreeNode* tmp = new TreeNode(newEntry);
            cur->setLeft(tmp); // Found spot
            return true;
        }
        else
            return insertHelper(newEntry, cur->getLeft() );
    }
    else { // Go right
        if (cur->getRight() == NULL){
            TreeNode* tmp = new TreeNode(newEntry);
            cur->setRight(tmp);
            return true;
        }
        else
            return insertHelper(newEntry, cur->getRight() );
    }
}

DBentry* TreeDB::find(string name){
    if (root == NULL) {
        return NULL;
    }
    return findHelper(name, root, 1);
}

DBentry* TreeDB::findHelper(string name, TreeNode* cur, int probes){
    if (cur == NULL)
        return NULL; //if not found

    if (name == cur->getEntry()->getName()){ //base case
        probesCount = probes; //sets probes count member to the number of probes needed to find node
        return cur->getEntry();
    }

    if (name < cur->getEntry()->getName()) // Go left
        return findHelper(name, cur->getLeft(), probes + 1); //adds 1 to probes needed

    else // Go right
        return findHelper(name, cur->getRight(), probes + 1);
}

bool TreeDB::remove(string name)
{
    if(root == NULL)//empty tree
    {
        cout << "Error: entry does not exist" << endl;
        return false;
    }
    bool check = false;
   root->deleteNode(root, name, check);
   if(!check)
   {
        cout << "Error: entry does not exist" << endl;
        return false;
   }
   return true;
}

void TreeDB::clear(){
    if (root != NULL)
        clearHelper(root);
    root = NULL; //set root to NULL for safety
}

void TreeDB::clearHelper(TreeNode* cur){
    if ((cur->getLeft() == NULL) && (cur->getRight() == NULL)){ //at node with no children
        delete cur;
        return;
    }
    else if ((cur->getLeft() == NULL) && (cur->getRight() != NULL)){ //if node only has children on right
        clearHelper(cur->getRight()); //go down right subtree
        delete cur;
        return;
    }
    else if ((cur->getLeft() != NULL) && (cur->getRight() == NULL)){ //if node only has children on left
        clearHelper(cur->getLeft()); //go down left subtree
        delete cur;
        return;
    }
    else{ //if node has 2 children
        clearHelper(cur->getLeft()); //go down both subtrees
        clearHelper(cur->getRight());
        delete cur;
        return;
    }
}

void TreeDB::printProbes() const{
    if(probesCount == 0)
        cout << "Error: entry does not exist\n";
    else
        cout << probesCount << endl;
}

void TreeDB::countActive(){
    activeCount = 0;
    if (root != NULL){ //makes sure tree is not empty
        activeHelper(root);
    }
    cout << activeCount << endl;
}

void TreeDB::activeHelper(TreeNode* cur){
    if (cur == NULL)
        return;

    if (cur->getEntry()->getActive() == true){
        activeCount += 1; //checks if active
    }
        activeHelper(cur->getLeft()); //goes down both subtrees
        activeHelper(cur->getRight());
}

void TreeDB::printAll(){
    if (root != NULL)
        printHelper(root);
}

void TreeDB::printHelper(TreeNode* cur){
    if (cur->getLeft() != NULL)
        printHelper(cur->getLeft()); //goes down left subtrees first to get names that come first alphabetically

    if (cur->getEntry()->getActive() == true) //prints names
        cout << cur->getEntry()->getName() << " : " << cur->getEntry()->getIPaddress() << " : active" << endl;
    else
        cout << cur->getEntry()->getName() << " : " << cur->getEntry()->getIPaddress() << " : inactive" << endl;
    if (cur->getRight() != NULL)
        printHelper(cur->getRight()); //goes down right subtree for names that come later
}