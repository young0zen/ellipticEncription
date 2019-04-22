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
    bool checkYourKey(long long key);
    vector<pair<int, long long>> getAllKeys();
    
    long long solveKey(vector<pair<int, long long>>);

private:
    const int shamirt;
    const int shamirn;
    vector<int> coefficients;
    vector<int> elements;
    vector<long long> shadowKey;
    
    static const int DISTRIBUTION_SIZE = 10;
    
    long long compute(long long x);
    
    vector<int> generateRandomNumbers(int n);
};

#endif /* shamir_hpp */
