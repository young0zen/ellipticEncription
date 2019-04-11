//
//  Elliptic.hpp
//  infoEnc
//
//  Created by wang on 2019/3/22.
//  Copyright © 2019 wang. All rights reserved.
//

#ifndef Elliptic_hpp
#define Elliptic_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include "util.hpp"

using std::pair;
using std::vector;

class Elliptic {
public:
    Elliptic(int a, int b, int p);
    ~Elliptic();
    
    /* print all points in the abel space */
    void ouputAllPoints();
    
    /*
     * compute n * G
     * Parameter:
     *      n, n in n * G
     * Return:
     *      the position in pair<int, int>
     * Same as multiplyPointBy when pass G as the first parameter
     */
    pair<int, int> GMultiplyBy(int n);
    /*
     * compute the (elliptic curve) sum of two points.
     * Parameter: two points given in pair<int, int>
     * Return: the sum of two points.
     */
    pair<int, int> addTwoPoints(pair<int, int>, pair<int, int>);
    
    /*
     * multiply a point by a number
     * Parameters: a point given in pair<int, int>, and a int n
     * Return: n * point
     */
    pair<int, int> multiplyPointBy(pair<int, int>, int);
    
    /* map a character to a point on curve */
    pair<int, int> getPointByChar(char ch);
    
    /* map a point on curve to a character */
    char getCharByPoint(pair<int, int> point);
    
private:
    int             a;                  /* parameter */
    int             b;                  /* parameter */
    int             p;                  /* modulo p */
    pair<int, int>  generator;
    
    vector<pair<int, int>> abelSet;
    
    void pickGenerator();
    
    /* check if a certain point is on the curve */
    bool isPointOnCurve(int x, int y);
    
    /* multiply the point by two */
    pair<int, int> doublePoint(pair<int, int> point);
    
    /* A helper function used in addTwoPoints. It use a magical formula
     * to compute the next point.
     * Paramter: two points and a int lambda
     * Return: the sum of two points.
     */
    pair<int, int> helpComputeNextPoint(pair<int, int>, pair<int, int>, int);
    
    void generateAbelSet();
};



#endif /* Elliptic_hpp */
