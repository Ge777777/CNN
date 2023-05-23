#pragma once

#include"tensor.h"
#include<vector>
#include<cstring>
#include<fstream>
#include<iostream>
#include<sstream>

struct case_s
{
    tensor<double> data,dataout;
    case_s(int x,int y,int z,int outx,int outy,int outz):data(x,y,z),dataout(outx,outy,outz){}
};

std::vector<case_s> read_csv(std::string filename = "../dataset/mnist_test.csv");

