//
//  Elliptic.cpp
//  infoEnc
//
//  Created by 王大头 on 2019/3/22.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#include "Elliptic.hpp"

Elliptic::Elliptic(int a, int b, int p) {
    this->a = a;
    this->b = b;
    this->p = p;
    pickGenerator();
}

Elliptic::~Elliptic() {
    
}

void Elliptic::ouputAllPoints() {
    std::pair<int, int> curr = generator;
    
    int i = 0;
    while(true) {
        std::cout << ++i << "P" << "(" << curr.first << ", " << curr.second << ")" << std::endl;
        curr = nextPoint(curr);
        if (curr.first == generator.first) {
            break;
        }
    }
    
    std::cout << ++i << "P" << "(" << curr.first << ", " << curr.second << ")" << std::endl;
    std::cout << "P(O)" << std::endl;
}

void Elliptic::pickGenerator() {
    std::cout << "Please specify a G for this elliptic curve"
    << std::endl;
    while(true) {
        std::cin >> generator.first >> generator.second;
        if (isPointOnCurve(generator.first, generator.second))
            break;
        
        std::cout << "Invalid position!" << std::endl;
    }
}

bool Elliptic::isPointOnCurve(int x, int y) {
    int left = pow(y, 2);
    int right = pow(x, 3) + a * x + b;
    
    return left % p == right % p;
}

std::pair<int, int> Elliptic::MultiplyPointBy(std::pair<int, int> p, int n) {
    std::pair<int, int> curr = p;
    while(--n) {
        curr = nextPoint(curr);
    }
    return curr;
}

std::pair<int, int> Elliptic::nextPoint(std::pair<int, int> point) {
    int numerator = 3 * pow(point.first, 2) + a;
    int denominator = 2 * point.second;
    int lambda = (numerator * Util::extEnclid(denominator, p)) % p;
    
    std::pair<int, int> next;
    next.first = lambda * lambda - point.first - point.first;
    next.second = lambda * (point.first - next.first) - point.second;
    return next;
}
