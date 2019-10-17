//
//  parallel_integral.cpp
//  parallel_integral
//
//  Created by Виктор Задябин on 17.10.2019.
//  Copyright © 2019 Виктор Задябин. All rights reserved.
//

#include "parallel_integral.hpp"

#include <future>
#include <iostream>
#include <cmath>
#include <vector>

namespace parallel_integral {

namespace {

static const double kAccuracy = 0.00001;

static const size_t t_size = std::thread::hardware_concurrency();

double Function(const double& arg){
    return 4*arg*arg*arg;
}

struct AccuracyParameters{
    double parts = 2;
    double step;
    const Limits limits;
    AccuracyParameters(const Limits& limits):limits(limits){
        step = (limits.right - limits.left)/parts;
    }
    void Increment(){
        parts *= 2;
        step = (limits.right - limits.left)/parts;
    }
    operator double(){
        return step;
    }
};



} //namespace

Limits::Limits(std::ifstream& input_file){
    input_file.open("input.txt");
    std::string l, r;
    input_file >> left >> right;
    input_file.close();
}

double ComputeIntegral (){
    std::ifstream input_file;
    const Limits limits(input_file);
    AccuracyParameters accuracy_parameters(limits);
    double previous_result = 0, result = 0;
    std::vector<std::future<double>> tasks(std::thread::hardware_concurrency());
    do {
        previous_result = result;
        result = 0;
        accuracy_parameters.Increment();
        size_t index = 0;
        if (accuracy_parameters.parts <= t_size){
            for (auto i = limits.left; i < limits.right; i += accuracy_parameters.step){
                result += accuracy_parameters.step*Function(i + accuracy_parameters.step/2);
            }
        }
        else {
            double step_for_task = accuracy_parameters.parts / t_size;
            for (auto i = limits.left; i < limits.right; i += step_for_task*accuracy_parameters.step){
                double left_p = i;
                double right_p = left_p + accuracy_parameters.step * step_for_task;
                tasks[index++] = std::async(std::launch::async, [left_p, right_p,                                           accuracy_parameters](){
                    double res = 0;
                    for (auto k = left_p; k < right_p; k += accuracy_parameters.step){
                        res += accuracy_parameters.step*Function(k + accuracy_parameters.step/2);
                    }
                    return res;
                });
            }
            for (auto&& adds : tasks){
                result+=adds.get();
            }
        }
        
    } while (abs(result - previous_result) >= kAccuracy);
    return result;
}


}
