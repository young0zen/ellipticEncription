//
//  util.cpp
//  infoEnc
//
//  Created by wang on 2019/3/23.
//  Copyright © 2019 wang. All rights reserved.
//
#include "util.hpp"
#include <iostream>
#include <algorithm>

/* compute d^-1 mod f using extender enclid algorithm
 * Parameter: d, f, which mean two numbers in "1/d modulo f"
 * Return:
 *      the result, -1 suggesting null
 */
int Util::extEnclid(int d, int f) {
    //if (d > f)
        //std::swap(d, f);
    
    int x1 = 1, x2 = 0, x3 = f;
    int y1 = 0, y2 = 1, y3 = d;
    int t1, t2, t3;
    
    while (true) {
        if (y3 == 0)
            return -1; /* no result */
        
        if (y3 == 1) {
            return convertToPositive(y2, f);
        }
        
        int q = x3 / y3;
        t1 = x1 - q * y1;
        t2 = x2 - q * y2;
        t3 = x3 - q * y3;
        
        x1 = y1;
        x2 = y2;
        x3 = y3;
        
        y1 = t1;
        y2 = t2;
        y3 = t3;
    }
}

/*
 * Convert an integer to smallest positive number and make sure
 * it has the same mudulo based on parameter p.
 * Return the positive number.
 */
int Util::convertToPositive(int original, int p) {
    while (original < 0) {
        original += p;
    }
    return original;
}
