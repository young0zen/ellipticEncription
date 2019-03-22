//
//  Elliptic.hpp
//  infoEnc
//
//  Created by 王大头 on 2019/3/22.
//  Copyright © 2019 unclesnake. All rights reserved.
//

#ifndef Elliptic_hpp
#define Elliptic_hpp

#include <stdio.h>

class Elliptic {
public:
    Elliptic();
    ~Elliptic();
    
    
private:
    int a;      /* parameter */
    int b;      /* parameter */
    int p;      /* modulo p */

};



#endif /* Elliptic_hpp */
