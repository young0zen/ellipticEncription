//
//  Elliptic.cpp
//  infoEnc
//
//  Created by wang on 2019/3/22.
//  Copyright © 2019 wang. All rights reserved.
//

#include "Elliptic.hpp"

using std::pair;
using std::cout;
using std::cin;
using std::endl;

Elliptic::Elliptic(int a, int b, int p) {
    this->a = a;
    this->b = b;
    this->p = p;
    pickGenerator();
    generateAbelSet();
}

Elliptic::~Elliptic() {
    
}

pair<int, int> Elliptic::GMultiplyBy(int n) {
    return multiplyPointBy(generator, n);
}

void Elliptic::generateAbelSet() {
    pair<int, int> curr = generator;
    
    while(true) {
        abelSet.push_back(curr);
        curr = addTwoPoints(curr, generator);
        if (curr.first == generator.first) {
            break;
        }
    }
    abelSet.push_back(curr);
}

void Elliptic::ouputAllPoints() {
    int i = 0;
    for (pair<int, int> point : abelSet) {
        cout << ++i << "P(" << point.first << ", " << point.second
                << ")" << endl;
    }
    cout << "P(O)" << endl;
}

void Elliptic::pickGenerator() {
    cout << "Please specify a G for this elliptic curve"
    << std::endl;
    while(true) {
        cin >> generator.first >> generator.second;
        if (isPointOnCurve(generator.first, generator.second))
            break;
        
        cout << "Invalid position!" << std::endl;
    }
}

bool Elliptic::isPointOnCurve(int x, int y) {
    int left = pow(y, 2);
    int right = pow(x, 3) + a * x + b;
    
    return left % p == right % p;
}

pair<int, int> Elliptic::multiplyPointBy(pair<int, int> p, int n) {
    pair<int, int> curr = p;
    while(--n) {
        curr = addTwoPoints(curr, p);
    }
    return curr;
}

pair<int, int> Elliptic::doublePoint(pair<int, int> point) {
    int numerator = 3 * pow(point.first, 2) + a;
    int denominator = 2 * point.second;
    /* these two numbers are all positive.. hopefully.. */

    int lambda = (numerator * Util::extEnclid(denominator, p)) % p;
    lambda = Util::convertToPositive(lambda, p);
    
    return helpComputeNextPoint(point, point, lambda);
}

pair<int, int> Elliptic::addTwoPoints(pair<int, int> pointa, pair<int, int> pointb) {
    if (pointa == pointb)
        return doublePoint(pointa);
    
    int numerator = pointb.second - pointa.second;
    int denominator = pointb.first - pointa.first;
    
    numerator = Util::convertToPositive(numerator, p);
    denominator = Util::convertToPositive(denominator, p);
    
    int lambda = (numerator * Util::extEnclid(denominator, p)) % p;
    lambda = Util::convertToPositive(lambda, p);
    
    return helpComputeNextPoint(pointa, pointb, lambda);
}

pair<int, int> Elliptic::helpComputeNextPoint(pair<int, int> pointa, pair<int, int> pointb, int lambda) {
    
    pair<int, int> next;
    next.first = (lambda * lambda - pointa.first - pointb.first) % p;
    next.second = (lambda * (pointa.first - next.first) - pointa.second) % p;
    
    next.first = next.first < 0 ? next.first + p : next.first;
    next.second = next.second < 0 ? next.second + p : next.second;
    return next;
}

pair<int, int> Elliptic::getPointByChar(char ch) {
    return abelSet.at(ch - 0); // user ascii
}

char Elliptic::getCharByPoint(pair<int, int> point) {
    for (int i = 0 ; i < abelSet.size(); i++) {
        if (i > 128)
            return '#';
        
        if (abelSet.at(i) == point) {
            return i; // use ascii
        }
    }
    
    return '#';
}
