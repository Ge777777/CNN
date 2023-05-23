#pragma once
#include "tensor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
struct case_s{
    tensor<double> data;
    tensor<double> dataout;
    case_s(int x,int y,int z,int x1,int y1,int z1):data(x,y,z),dataout(x1,y1,z1){};
};

std::vector<case_s> read_csv(const std::string& filename);

void pre_read(std::string path);