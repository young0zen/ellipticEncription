//
//  main.cpp
//  infoEnc
//
//  Created by 王大头 on 2019/3/22.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Elliptic.hpp"
#include "util.hpp"

using namespace std;

class Tester {
    typedef bool (*testfun)();
    
public:
    Tester() {
        
    }
    
    void testAll() {
        cout << (testExtEnclid() ? "Pass!" : "Failed!") << endl;
        testOutputAll();
    }
    
    bool testExtEnclid() {
        cout << __func__ << endl;
        bool flag = 1;
        flag  = flag && Util::extEnclid(5, 17) == 7;
        flag = flag && Util::extEnclid(6, 17) == 3;
        flag = flag && Util::extEnclid(7, 96) == 55;
        
        return flag;
    }
    
    void testOutputAll() {
        Elliptic ell(1, 1, 23);
        ell.ouputAllPoints();
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    //Elliptic ell(0, -4, 211);
    
    Tester test;
    test.testOutputAll();
    
    return 0;
}


