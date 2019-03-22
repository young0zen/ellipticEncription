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
        std::cout << i++ << "P" << "(" << curr.first << ", " << curr.second << ")" << std::endl;
        if (curr.first == generator.first) {
            std::cout << "P(O)" << std::endl;
            break;
        }
        curr = nextPoint(curr);
        
    }
}

