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
    const int       THRESHOLD = 1e-5;
    std::pair<int, int> generator;
    
    void pickGenerator() {
        std::cout << "Please specify a G for this elliptic curve"
                << std::endl;
        while(true) {
            std::cin >> generator.first >> generator.second;
            if (isPointOnCurve(generator.first, generator.second))
                break;
            
            std::cout << "Invalid position!" << std::endl;
        }
    }
    
    bool isPointOnCurve(int x, int y) {
        return pow(y, 2) - (pow(x, 3) + a * x + b) < THRESHOLD;
    }
    
    std::pair<int, int> MultiplyPointBy(std::pair<int, int> p, int n) {
        std::pair<int, int> curr = p;
        while(--n) {
            curr = nextPoint(curr);
        }
        return curr;
    }
    
    std::pair<int, int> nextPoint(std::pair<int, int> p) {
        double lambda = (3 * pow(p.first, 2) + a) /
                (2 * p.second);
        
        
    }
};



#endif /* Elliptic_hpp */
