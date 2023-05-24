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

struct case_s
{
    tensor<int> data,dataout;
    case_s(int x,int y,int z,int outx,int outy,int outz):data(x,y,z),dataout(outx,outy,outz){}
};

std::vector<case_s> read_csv(std::string filename = "../dataset/test.csv");

