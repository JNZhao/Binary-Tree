/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DBentry.h"


//constructor & destructor

DBentry::DBentry(){
    
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name; //sets members
    IPaddress = _IPaddress;
    active = _active;
}

DBentry::~DBentry(){

}

void DBentry::setName(string _name){
    name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}

void DBentry::setActive (bool _active){
    active = _active;
}

string DBentry::getName() const{
    return name;
}

unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}

bool DBentry::getActive() const{
    return active;
}