//
//  main.cpp
//  infoEnc
//
//  Created by wang on 2019/3/22.
//  Copyright © 2019 wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Elliptic.hpp"
#include "util.hpp"

using namespace std;

class Tester {
    
public:
    Elliptic ell;
    
    Tester()
    :ell(1, 1, 23) {
        //Elliptic ell(1, 1, 23);
    }
    
    void testAll() {
        cout << (testExtEnclid() ? "Pass!" : "Failed!") << endl;
        testOutputAll();
    }
    
    bool testExtEnclid() {
        cout << __func__ << endl;
        bool flag = 1;
        flag = flag && Util::extEnclid(5, 17) == 7;
        flag = flag && Util::extEnclid(6, 17) == 3;
        flag = flag && Util::extEnclid(7, 96) == 55;
        
        return flag;
    }
    
    void testOutputAll() {
        ell.ouputAllPoints();
    }
    
    void testAddTwoPoints() {
        pair<int, int> a(3, 10), b(13, 16), tmp;
        tmp = ell.addTwoPoints(a, b);
        if (tmp.first != 0 || tmp.second != 1) {
            cout << "failed, expected (0, 1), found ("
                    << tmp.first << ", "  << tmp.second << ")." << endl;
        } else {
            cout << "(" << tmp.first << ", "  << tmp.second << "). Pass!" << endl;
        }
        
        b.first = 7;
        b.second = 12;
        
        tmp = ell.addTwoPoints(a, b);
        if (tmp.first != 19 || tmp.second != 5) {
            cout << "failed, expected (0, 1), found ("
            << tmp.first << ", "  << tmp.second << ")." << endl;
        } else {
            cout << "(" << tmp.first << ", "  << tmp.second << "). Pass!" << endl;
        }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    //Elliptic ell(0, -4, 211);
    
    Tester test;
    test.testOutputAll();
    test.testAddTwoPoints();
    
    return 0;
}


