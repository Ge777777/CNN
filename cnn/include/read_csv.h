#pragma once

#include"tensor.h"
#include<vector>
#include<string.h>

struct case_s
{
    tensor<double> data,dataout;
};

std::vector<case_s> read_csv();

void pre_read(std::string path);