//
//  equation.hpp
//  news360
//
//  Created by Shangwei Xie on 5/4/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#ifndef equation_hpp
#define equation_hpp

#include <stdio.h>
#include <list>
#include "summand.hpp"


class equation{
    bool arranged;
    std::list<summand> theSummands;
    
    equation processStrLeftSide(const std::string& x,std::string::iterator& start,const std::string::iterator& end);
    equation processBtwPlsMns(const std::string& x,std::string::iterator& start,const std::string::iterator& end);
    
    void arrange();
    
public:
    equation();
    equation(std::list<summand> _theSummands);
    equation(const summand& x);
    equation(std::string x);
    
    void plus(const summand& s);
    void plus( equation& eq2);
    void multiply( summand& s);
    void multiply( equation& eq2);

    std::string print();

};


#endif /* equation_hpp */
