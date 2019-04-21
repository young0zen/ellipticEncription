//
//  main.cpp
//  shamir
//
//  Created by ScottWang on 2019/4/11.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#include <iostream>
#include "shamir.hpp"

using namespace std;

int main() {
    ShamirCenter sha(5, 10);
    vector<pair<int, long long>> list = sha.getAllKeys();
    for (int i = 0; i < list.size(); i++) {
        cout << "(" << list[i].first << " " << list[i].second
            << ")" << endl;
    }
    
    long long key = sha.solveKey(list);
    cout << sha.checkYourKey(key) << endl;
}
