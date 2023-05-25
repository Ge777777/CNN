#pragma once

#include"tensor.h"
#include<vector>
#include<cstring>
#include<fstream>
#include<iostream>
#include<sstream>

const int header = 1;

const int in_x = 28;

const int in_y = 28;

const int in_z = 1;

const int out_x = 10;

const int out_y = 1;

const int out_z = 1;

struct IOData
{
    tensor<double> grayPixels,outputVector;
    IOData(int x, int y, int z, int outx, int outy, int outz): grayPixels(x, y, z), outputVector(outx, outy, outz){}
    ~IOData() = default;
};

std::vector<IOData> read_csv(std::string filename = "../dataset/mnist_train.csv");

