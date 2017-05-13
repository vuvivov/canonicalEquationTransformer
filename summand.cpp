//
//  summand.cpp
//  news360
//
//  Created by Shangwei Xie on 5/4/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#include "summand.hpp"




summand::summand(){
    coefficient=0;
    order.assign(nLetterVec, 0);
}

summand::summand(const double& _coefficient,const std::vector<int> _order):coefficient(_coefficient),order(_order){
}

summand::summand(std::string str):summand(){
    std::string::iterator it,itStart,itVar;
    //find sign and clean format
    coefficient=1;
    std::stack<long> iErase;
    for (it=str.begin(); it!=str.end(); it++){
        if(!(isLetter(*it)|isNum(*it)|(*it=='^'))){
            if (*it=='-') {
                coefficient=-1;
            }
            iErase.push(it-str.begin());
        }
    }
    long sErase=iErase.size();
    for (int i=0; i<sErase; i++) {
        str.erase(iErase.top(),1);
        iErase.pop();
    }

    //find first letter
    for (it=str.begin(); it!=str.end(); it++){
        if (isLetter(*it)) {
            break;
        }
    }
    //find coeff
    if (isNum(str.front())) {
        coefficient*=std::stod(str.substr(0,it-str.begin()));
    }
    //find variable and order
    while (it!=str.end()) {
        itVar=it;
        for (it=it+1; it!=str.end(); it++) {
            if (*it=='^') {
                itStart=it+1;
            }
            if (isLetter(*it)) {
                break;
            }
        }
        if (it>itVar+1) {
            order[*itVar]+=std::stoi(str.substr(itStart-str.begin(),it-itStart));
        }
        else{
            order[*itVar]+=1;
        }
    }
}


bool summand::isNum(int x){
    return (x=='.')|('0'<=x&x<='9');
}

bool summand::isLetter(int x){
    return (x>='A'&x<='Z')|(x>='a'&x<='z');
}

std::string summand::printVariable(int i){
    std::string output;
    if (order[i]>0) {
        output+=(char)i;
        if (order[i]>1) {
            output+='^';
            output+=std::to_string(order[i]);
        }
    }
    return output;
}


std::string summand::print(){
    if (coefficient==0) {
        return "";
    }
    
    std::string output;
    //coefficient
    if (coefficient!=1) {
        if (coefficient==-1) {
            output="-";
        }
        else{
            output=std::to_string(coefficient);
        }
    }
    //'+' sign
    if (coefficient>0) {
        output='+'+output;
    }
    //remove 0 at end
    std::string::reverse_iterator it;
    for (it=output.rbegin(); it!=output.rend(); it++) {
        if (*it!='0') {
            break;
        }
    }
    output=output.substr(0,output.rend()-it);
    //remove . at end
    if (output.back()=='.') {
        output.pop_back();
    }
    
    //variable
    for (int i='A'; i<='Z'; i++) {
        output+=printVariable(i);
    }
    for (int i='a'; i<='z'; i++) {
        output+=printVariable(i);
    }
    
    if (((output=="+")|output=="-")&((coefficient==1)|(coefficient==-1))) {
        output+='1';
    }
    return output;
}


//compare summand(ignore coeff)
bool summand::operator==(const summand &x){
    for (int i='A'; i<='Z'; i++) {
        if (order[i]!=x.order[i]) {
            return false;
        }
    }
    for (int i='a'; i<='z'; i++) {
        if (order[i]!=x.order[i]) {
            return false;
        }
    }
    return true;
}

void summand::addCoeff(summand &x){
    coefficient +=x.coefficient;
}

void summand::multiply(summand &x){
    coefficient*=x.coefficient;
    for (int i='A'; i<='Z'; i++) {
        order[i]+=x.order[i];
    }
    for (int i='a'; i<='z'; i++) {
        order[i]+=x.order[i];
    }
}


int summand::getOrder(int i)const{
    return order[i];
}


bool operator<(const summand& x,const summand& y){
    for (int i='A'; i<='Z'; i++) {
        if (x.getOrder(i)<y.getOrder(i)) {
            return true;
        }
        if (x.getOrder(i)>y.getOrder(i)) {
            return false;
        }
    }
    for (int i='a'; i<='z'; i++) {
        if (x.getOrder(i)<y.getOrder(i)) {
            return true;
        }
        if (x.getOrder(i)>y.getOrder(i)) {
            return false;
        }
    }
    return false;
}



