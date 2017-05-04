/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jiananzhao
 *
 * Created on November 23, 2016, 6:47 PM
 */

#include <iostream> //standard header files to allow for use of strings, stringstreams, etc.
#include <string>
#include <sstream>
#include <iomanip>

#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

int main(){
    TreeDB treeDB;

    cout.setf (ios::fixed); //make sure everything prints as decimals and not scientific notation

    string line;
    int IPaddress; //used temporarily to store any integer user inputs

    while (!cin.eof()){
        string command,name, status; //variables for string arguments. Inside loop because I need to reinitate to null string every loop through

        cout << "> ";

        if (cin.eof()) //if end of file, exit loop
            break;

        getline(cin, line); //gets user input.
        stringstream linestream (line);

        linestream >> command;

        if (command == "insert"){
            bool inSerted;
            linestream >> name >> IPaddress >> status;
            if (status == "active"){
                DBentry* tmp = new DBentry(name, IPaddress, true); //creates new DBentry object and inserts
                inSerted = treeDB.insert(tmp); //insert returns bool of whether insert was successful or not
            }
            else{
                DBentry* tmp = new DBentry(name, IPaddress, false);
                inSerted = treeDB.insert(tmp);
            }
            if (inSerted == true) //if inserted
                cout << "Success" << endl;
            else if (inSerted == false) //if not inserted
                cout << "Error: entry already exists" << endl;
        }

        else if (command == "remove"){
            linestream>> name;
            bool isRemoved=treeDB.remove(name);
            if(isRemoved)
                cout << "Success" <<endl;
            else
                cout << "Error: entry does not exist" <<endl;
        }

        else if (command == "find"){
            linestream >> name;
            DBentry* temp=treeDB.find(name);
            
            if (temp == NULL) 
                cout << "Error: entry does not exist" << endl;
            else{ 
                if (temp->getActive() == true)
                    cout << temp->getName() << " : " << temp->getIPaddress() << " : active" << endl;
                else
                    cout << temp->getName() << " : " << temp->getIPaddress() << " : inactive" << endl;
            }
        }

        else if (command == "printall"){
            treeDB.printAll();
        }

        else if (command == "printprobes"){
            linestream >> name;
            DBentry* temp = treeDB.find(name); //this is needed because the find function also sets number of probes needed to find an entry
            if (temp != NULL){
                treeDB.printProbes();
            }
            else
                cout << "Error: entry does not exist" << endl;
        }

        else if (command == "removeall"){
            treeDB.clear();
            cout << "Success" << endl;

        }

        else if (command == "countactive"){
            treeDB.countActive();
        }

        else if (command == "updatestatus"){
            linestream >> name >> status;
            DBentry* tmp=treeDB.find(name);
            
            if (status == "active" && tmp != NULL){
                tmp->setActive(true); 
            }
            else if (status == "inactive" && tmp != NULL)
                tmp->setActive(false); 
            if (tmp == NULL) 
                cout << "Error: entry does not exist" << endl;
            else
                cout << "Success" << endl;
        }
        linestream.clear(); 
        linestream.ignore(1000,'\n');
    }
    return 0;
}
