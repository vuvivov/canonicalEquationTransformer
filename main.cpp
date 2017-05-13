//
//  main.cpp
//  news360
//
//  Created by Shangwei Xie on 5/4/17.
//  Copyright © 2017 Shangwei Xie. All rights reserved.
//

#include "equation.hpp"
#include "summand.hpp"
#include "unitTest.hpp"
#include <fstream>


std::string transform(std::string x);
void fileMode();
void interactiveMode();

int main ()
{
    //unit test
    std::cout<<"summand unit test: "<<(summandUnitTest()?"passed":"failed")<<"\n"
    <<"equation unit test: "<<(equationUnitTest()?"passed":"failed")<<"\n";
    
    
    //application
    std::cout<<"Please select by enter the corresponding number:\n1. File mode\n2. Interactive mode\n";
    std::string in;
    std::cin>>in;
    if ((in=="1")|(in=="2")) {
        if (in=="1") {
            fileMode();
        }
        else {
            interactiveMode();
        }
    }
    else{
        std::cout<<"Please enter \"1\" or \"2\"\n";
    }

    return 0;
}


std::string transform(std::string x){
    equation a(x);
    return a.print();
}



void fileMode(){
    std::cout<<"please enter working directory:\n";
    std::string dir;
    std::cin>>dir;
    std::cout<<"please enter input file name:\n";
    std::string in;
    std::cin>>in;
    
    std::ifstream fileIn;
    std::string str;
    fileIn.open (dir+"/"+in);
    
    std::ofstream fileOut;
    fileOut.open(dir+"/"+"output.out");
    
    while (std::getline(fileIn, str)) {
        fileOut<<transform(str)<<"\n";
    }
    fileIn.close();
    fileOut.close();
}

void interactiveMode(){
    std::string str;
    while (1) {
        std::cout<<"please enter an equation (to exit, press Ctrl+C)\n";
        std::cin>>str;
        std::cout<<transform(str)<<"\n";
    }
}

































































