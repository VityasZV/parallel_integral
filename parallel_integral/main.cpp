//
//  main.cpp
//  parallel_integral
//
//  Created by Виктор Задябин on 17.10.2019.
//  Copyright © 2019 Виктор Задябин. All rights reserved.
//

#include "parallel_integral/parallel_integral.hpp"

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << parallel_integral::ComputeIntegral() << std::endl;
    return 0;
}
