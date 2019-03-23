//
//  Elliptic.hpp
//  infoEnc
//
//  Created by 王大头 on 2019/3/22.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#ifndef Elliptic_hpp
#define Elliptic_hpp

#include <iostream>
#include <cmath>
#include "util.hpp"

class Elliptic {
public:
    Elliptic(int a, int b, int p);
    ~Elliptic();
    
    /* print all points in the abel space */
    void ouputAllPoints();
    
    /*
     * get n * G
     * Parameter:
     *      n, n in n * G
     * Return:
     *      the position in pair<int, int>
     */
    std::pair<int, int> GMultiplyBy(int n);
    
    
    
private:
    int             a;                  /* parameter */
    int             b;                  /* parameter */
    int             p;                  /* modulo p */
    std::pair<int, int> generator;
    
    void pickGenerator();
    
    bool isPointOnCurve(int x, int y);
    
    std::pair<int, int> MultiplyPointBy(std::pair<int, int>, int);
    
    std::pair<int, int> nextPoint(std::pair<int, int> point);
};



#endif /* Elliptic_hpp */
