//
//  shamir.hpp
//  shamir
//
//  Created by ScottWang on 2019/4/11.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#ifndef shamir_hpp
#define shamir_hpp

#include <stdio.h>
#include <vector>

using std::vector;
using std::pair;

class ShamirCenter {
public:
    ShamirCenter(int t, int n);
    vector<int> getElements();
    bool checkYourKey(int key);
    pair<int, int> getPartialKey();

private:
    const int shamirt;
    const int shamirn;
    vector<int> coefficients;
    vector<int> elements;
    vector<int> shadowKey;
    int count = 0;
    
    static const int DISTRIBUTION_SIZE = 100;
    
    long long compute(long long x);
};

#endif /* shamir_hpp */
