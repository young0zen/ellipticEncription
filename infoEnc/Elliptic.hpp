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

using std::pair;

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
    pair<int, int> GMultiplyBy(int n);
    pair<int, int> addTwoPoints(pair<int, int>, pair<int, int>);
    
private:
    int             a;                  /* parameter */
    int             b;                  /* parameter */
    int             p;                  /* modulo p */
    pair<int, int> generator;
    
    void pickGenerator();
    
    bool isPointOnCurve(int x, int y);
    
    pair<int, int> multiplyPointBy(pair<int, int>, int);
    
    pair<int, int> doublePoint(pair<int, int> point);
    
    //pair<int, int> addTwoPoints(pair<int, int>, pair<int, int>);
    
    pair<int, int> helpComputeNextPoint(pair<int, int>, pair<int, int>, int);
};



#endif /* Elliptic_hpp */
