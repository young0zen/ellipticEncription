//
//  shamir.cpp
//  shamir
//
//  Created by ScottWang on 2019/4/11.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#include "shamir.hpp"
#include <random>
#include <cassert>

ShamirCenter::ShamirCenter(int t, int n)
:shamirn(n), shamirt(t){
    assert(t < n && t > 0 && n > 0);
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, DISTRIBUTION_SIZE);
    auto dice = std::bind(distribution, generator);
    
    for (int i = 0; i < shamirt; i++) {
        coefficients.push_back(dice());
    }
    
    for (int i = 0; i < shamirn; i++) {
        elements.push_back(dice());
    }
    
    
}

vector<int> ShamirCenter::getElements() {
    return elements;
}

bool ShamirCenter::checkYourKey(int key) {
    return key == coefficients[0];
}

pair<int, int> ShamirCenter::getPartialKey() {
    if (count == elements.size()) {
        
    }
    long long x = elements[count++];
    long long y = compute(x);
    
    return std::make_pair(x, y);
}

long long ShamirCenter::compute(long long x) {
    long long res = 0;
    for (int i = 0; i < shamirt; i++) {
        res += coefficients[i] * pow(x, i);
    }
    return res;
}


