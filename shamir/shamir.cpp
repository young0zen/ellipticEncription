//
//  shamir.cpp
//  shamir
//
//  Created by ScottWang on 2019/4/11.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#include "shamir.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

void printVector(vector<int> v) {
    for(auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

ShamirCenter::ShamirCenter(int t, int n)
:shamirn(n), shamirt(t){
    assert(t < n && t > 0 && n > 0);
    
    
    coefficients = generateRandomNumbers(shamirt);
    elements = generateRandomNumbers(shamirn);
    
    printVector(coefficients);
    
    std::cout << "shadowKey ";
    for (int i = 0; i < shamirn; i++) {
        shadowKey.push_back(compute(elements[i]));
        std::cout << shadowKey[i] << " ";
    }
    std::cout << std::endl;
}

vector<int> ShamirCenter::getElements() {
    return elements;
}

bool ShamirCenter::checkYourKey(long long key) {
    std::cout << "expected: " << coefficients[0]
    << " found: " << key << std::endl;
    return key == coefficients[0];
}

vector<pair<int, long long>> ShamirCenter::getAllKeys() {
    vector<pair<int, long long> > res;
    for (int i = 0; i < shamirn; i++) {
        res.push_back(std::make_pair(elements[i], shadowKey[i]));
    }
    return res;
}

long long ShamirCenter::compute(long long x) {
    long long res = 0;
    for (int i = 0; i < shamirt; i++) {
        res += coefficients[i] * pow(x, i);
    }
    return res;
}

long long ShamirCenter::solveKey(vector<pair<int, long long> > points) {
    double sum = 0;
    for (int i = 0; i < shamirt; i++) {
        double mul = 1;
        for (int j = 0; j < shamirt; j++) {
            if (i != j) {
                mul *= -points[j].first * 1.0 / (points[i].first - points[j].first);
            }
        }
        
        sum += points[i].second * mul;
    }
    
    std::cout << "sum: " << sum << std::endl;
    sum = round(sum);
    return sum;
}

int myrandom (int i) { return std::rand()%i;}

vector<int> ShamirCenter::generateRandomNumbers(int n) {
    std::srand(unsigned(std::time(0)));
    vector<int> res;
    for (int i = 1; i <= n; i++) {
        res.push_back(i);
    }
    
    std::random_shuffle(res.begin(), res.end(), myrandom);
    return res;
}
