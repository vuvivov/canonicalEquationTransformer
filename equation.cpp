//
//  equation.cpp
//  news360
//
//  Created by Shangwei Xie on 5/4/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#include "equation.hpp"

equation::equation():arranged(false){};


equation::equation(std::list<summand> _theSummands):equation(){
    theSummands=theSummands;
}

equation::equation(const summand& x):equation(){
    theSummands.push_back(x);
}

equation::equation(std::string x):equation(){
    //separate left & right
    std::string::iterator it=x.begin();
    for (it; it!=x.end(); it++) {
        if (*it=='=') {
            break;
        }
    }
    std::string::iterator itLeftStart=x.begin();
    std::string::iterator itLeftEnd=it;
    std::string::iterator itRightStart=it+1;
    std::string::iterator itRightEnd=x.end();
    equation left=processStrLeftSide(x,itLeftStart,itLeftEnd);
    equation right=processStrLeftSide(x,itRightStart,itRightEnd);
    this->plus(left) ;
    summand negOne=summand("-1");
    right.multiply(negOne);
    this->plus(right);
    arrange();
}



void equation::arrange(){
    
    if (!arranged) {
        arranged=true;
        theSummands.sort();
        //combine same terms
        std::list<summand>::iterator it1,it2;
        it2=theSummands.begin();
        it2++;
        for (it2; it2!=theSummands.end(); it2++) {
            it1=it2;
            it1--;
            if (*it1==*it2) {
                it2->addCoeff(*it1);
                theSummands.erase(it1);
            }
        }
    }
     
}

equation equation::processStrLeftSide(const std::string& x,std::string::iterator& start,const std::string::iterator& end){
    equation output;
    while ((start!=end)&(*start!=')')) {
        equation temp=processBtwPlsMns(x, start, end);
        output.plus(temp);
        
    }
    if (start!=end) {
        start++;
    }
    return output;
}

equation equation::processBtwPlsMns(const std::string& x,std::string::iterator& start,const std::string::iterator& end){
    summand s("1");
    equation output;
    output.plus(s);
    std::string::iterator it=start;
    std::string::iterator initial=start;
    //special cases
    while (it!=end) {
        if (((*it=='+')|(*it=='-')|(*it==')'))&(it!=initial)) {
            if (start==initial) {
                summand temp(x.substr(start-x.begin(),it-start));
                output.multiply(temp);
                
                start=it;
            }
            return output;
        }
        else if(*it=='('){
            summand temp(x.substr(start-x.begin(),it-start));
            output.multiply(temp);
            it++;
            equation temp2=processStrLeftSide(x, it, end);
            output.multiply(temp2);
            start=it;
        }
        else{
            it++;
        }
    }
    //if no special case detected above, return simple summand from "start"
    if (start!=end) {
        summand temp(x.substr(start-x.begin(),it-start));
        output.multiply(temp);
        
        start=end;
    }
    
    return output;
}

void equation::plus(const summand& s){
    arranged=false;
    theSummands.push_back(s);
}

void equation::plus( equation &eq2){
    for (std::list<summand>::iterator it=eq2.theSummands.begin(); it!=eq2.theSummands.end(); it++) {
        plus(*it);
    }
}

void equation::multiply( summand& s){
    arranged=false;
    for (std::list<summand>::iterator it=theSummands.begin(); it!=theSummands.end(); it++) {
        it->multiply(s);
    }
}

void equation::multiply( equation& eq2){
    equation eqCopy=*this;
    equation eqCopy2;
    theSummands.clear();
    for (std::list<summand>::iterator it=eq2.theSummands.begin(); it!=eq2.theSummands.end(); it++) {
        eqCopy2=eqCopy;
        eqCopy2.multiply(*it);
        plus(eqCopy2);
    }
}

std::string equation::print(){
    arrange();
    std::list<summand>::reverse_iterator it=theSummands.rbegin();
    std::string output=it->print();
    if (output.front()=='+') {
        output.erase(0,1);
    }
    it++;
    for (it; it!=theSummands.rend(); it++) {
     output+=it->print();
    }
    if (output.empty()) {
     output+="0";
    }
    output+="=0";

    return output;
}