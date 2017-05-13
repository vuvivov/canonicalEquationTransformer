//
//  summand.hpp
//  news360
//
//  Created by Shangwei Xie on 5/4/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#ifndef summand_hpp
#define summand_hpp


#include <vector>
#include <string>
#include <stack>
#include <iostream>


#define nLetterVec 128

class summand{
    double coefficient;
    std::vector<int> order;//order of variables
    
    bool isNum(int x);
    bool isLetter(int x);
    
    std::string printVariable(int i);
    
    
public:
    summand();
    summand(const double& _coefficient,const std::vector<int> _order);
    summand(std::string str);
    std::string print();
    
    bool operator==(const summand& x);
    
    void addCoeff(summand& x);
    void multiply(summand& x);
    
    int getOrder (int i)const;
    
    
};

bool operator<(const summand& x,const summand& y);

#endif /* summand_hpp */
