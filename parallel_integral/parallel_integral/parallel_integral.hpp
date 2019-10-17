//
//  parallel_integral.hpp
//  parallel_integral
//
//  Created by Виктор Задябин on 17.10.2019.
//  Copyright © 2019 Виктор Задябин. All rights reserved.
//

#ifndef parallel_integral_hpp
#define parallel_integral_hpp

#include <fstream>

namespace parallel_integral {
        
struct Limits {
    double left;
    double right;
    Limits(std::ifstream& input_file);
};

/// Parallel computing of integral
double ComputeIntegral ();

}// parallel_integral


#endif /* parallel_integral_hpp */
