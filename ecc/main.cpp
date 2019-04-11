//
//  main.cpp
//  infoEnc
//
//  Created by wang on 2019/3/22.
//  Copyright © 2019 wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Elliptic.hpp"
#include "util.hpp"
//#include "User.h"

using namespace std;

/*
class Tester {
    
public:
    Elliptic ell;
    
    Tester()
    :ell(0, -4, 211) {
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
    
    void testGetPointAndChar() {
        pair<int, int> tmp(74, 201), t;
        char ch;
        if ((ch = ell.getCharByPoint(tmp)) == 'a') {
            cout << "a PASS!" << endl;
        }
        
        t = ell.getPointByChar('b');
        if (t.first == 94 && t.second == 154) {
            cout << "PASS" << endl;
        } else {
            cout << "FAIL" << endl;
        }
        
    }
    
};
*/


int main() {
	/*
	User A;
	User B(0,-4,211);
	B.getEQG(B.sendCurve(), B.generateQ(), B.generateG());
	string code = "I am a boy";
	for (int i = 0; i < code.size(); ++i)
	{
		A.codeIntoCurve(code[i]);
		B.getC1AndC2(A.generateC1(), A.generateC2());
		cout << B.decode(B.calculateM()) << " ";
	}s

	cout << "end" << endl;

	*/
    return 0;
}


