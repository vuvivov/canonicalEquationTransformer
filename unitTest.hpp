//
//  unitTest.hpp
//  news360
//
//  Created by Shangwei Xie on 5/11/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#ifndef unitTest_hpp
#define unitTest_hpp

#include <stdio.h>
#include "equation.hpp"

class testStr{
    std::string a;
    std::string b;
    
public:
    testStr(std::string _a,std::string _b):a(_a),b(_b){};
    std::string getA(){return a;};
    std::string getB(){return b;};
};

bool summandUnitTest();
bool equationUnitTest();

#endif /* unitTest_hpp */
