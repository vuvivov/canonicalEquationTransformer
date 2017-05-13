//
//  unitTest.cpp
//  news360
//
//  Created by Shangwei Xie on 5/11/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#include "unitTest.hpp"

bool summandUnitTest(){
    std::vector<testStr> summands;
    
    //test summand building and printing
    summands.push_back(testStr(" -0.45670ddx^2 y ^78dSfs^ 3A^45","-0.4567A^45Sd^3fs^3x^2y^78"));
    summands.push_back(testStr(" + 23 45 ","+2345"));
    summands.push_back(testStr(" - 23 45 ","-2345"));
    summands.push_back(testStr("2345","+2345"));
    summands.push_back(testStr("-2345.0","-2345"));
    summands.push_back(testStr(" - E Fi dj ","-EFdij"));
    summands.push_back(testStr(" -1 E Fi d^1j ","-EFdij"));
    summands.push_back(testStr("0",""));
    summands.push_back(testStr("0asdf",""));
    summands.push_back(testStr("-","-1"));
    summands.push_back(testStr("","+1"));
    
    for (std::vector<testStr>::iterator it=summands.begin();it!=summands.end();it++) {
        summand a(it->getA());
        if (a.print()!=it->getB()) {
            std::cout<<it->getB()<<"!="<<a.print()<<"\n";
            return false;
        }
    }
    
    //test compasion
    summands.clear();
    std::vector<bool> isLarger;
    summands.push_back(testStr("a^2","a^3"));isLarger.push_back(1);
    summands.push_back(testStr("a^2","b^1"));isLarger.push_back(0);
    summands.push_back(testStr("abc","ab"));isLarger.push_back(0);
    summands.push_back(testStr("a^3b^2c","a^3b^2c^6"));isLarger.push_back(1);
    summands.push_back(testStr("333","a"));isLarger.push_back(1);
    
    
    for (int i=0;i<summands.size();i++) {
        summand a(summands[i].getA());
        summand b(summands[i].getB());
        if ((a<b)!=isLarger[i]) {
            std::cout<<summands[i].getA()<<"!<"<<summands[i].getA()<<"\n";
            return false;
        }
    }
    
    return true;
}


bool equationUnitTest(){
    //test arrange
    equation a(summand("3cab")),b(summand("ba^2c")),c(summand("-3.40")),d(summand("-0.03xz^2y"));
    equation A,B;
    
    A=equation();B=equation();
    A.plus(a);A.plus(b);A.plus(c);A.plus(d);
    if (A.print()!="a^2bc+3abc-0.03xyz^2-3.4=0") {
        return false;
    }
    
    A=equation();B=equation();
    A.plus(a);B.plus(b);B.plus(c);B.plus(d);A.plus(B);
    if (A.print()!="a^2bc+3abc-0.03xyz^2-3.4=0") {
        return false;
    }
    
    A=equation();B=equation();
    A.plus(a);A.plus(b);A.plus(c);B.plus(d);A.multiply(B);
    if (A.print()!="-0.03a^2bcxyz^2-0.09abcxyz^2+0.102xyz^2=0"){
        return false;
    }
    
    A=equation();B=equation();
    A.plus(a);A.plus(b);B.plus(c);B.plus(d);B.multiply(A);
    if (B.print()!="-0.03a^2bcxyz^2-3.4a^2bc-0.09abcxyz^2-10.2abc=0"){
        return false;
    }
    
    std::vector<testStr> equations;
    //test equation building and printing
        //in task description
    equations.push_back(testStr("x^2+3.5xy+y=y^2-xy+y", "x^2+4.5xy-y^2=0"));
    equations.push_back(testStr("x=1", "x-1=0"));
    equations.push_back(testStr("x-(y^2-x)=0", "2x-y^2=0"));
    equations.push_back(testStr("x-(0-(0-x))=0", "0=0"));
        //additional
    equations.push_back(testStr("x=(yz)-1", "x-yz+1=0"));
    equations.push_back(testStr("(x^2)+(3.5)(x)(y)+y=(((y^2)-(((x)(y))))+y)", "x^2+4.5xy-y^2=0"));
    equations.push_back(testStr("x=(2+0x)-0", "x-2=0"));
    equations.push_back(testStr("x-1(y^2-x)1=0", "2x-y^2=0"));
    equations.push_back(testStr("(((((x)))))-(0-(0-x))=(0)", "0=0"));
    equations.push_back(testStr("0=x^6yz-zx^6y", "0=0"));
    equations.push_back(testStr("abc=abc+0", "0=0"));
    equations.push_back(testStr("abc-bcd=0", "abc-bcd=0"));
    
    for (std::vector<testStr>::iterator it=equations.begin();it!=equations.end();it++) {
        equation a(it->getA());
        if (a.print()!=it->getB()) {
            std::cout<<it->getB()<<"!="<<a.print()<<"\n";
            return false;
        }
    }
    return true;
}