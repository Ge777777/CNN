#pragma once

#include"tensor.h"
#include<vector>
#include<chrono>
#include<random>
#include<string.h>

double rate = 0.01;//学习速率

const double up=0.1,down=0;//权值初始随机范围

const int basic_x=28,basic_y=28,baisc_z=1; //初始矩阵大小

const double cutrate=0;

const int extend_flitter_stride=1;//卷积层步幅
const int extend_flitter_size=3;//卷积核大小
const int extend_flitter_len=3;//卷积核数

const int pool_extend_flitter_stride=2;//池化步幅
const int pool_extend_flitter_size=2;//池化矩阵大小
const int pool_extend_flitter_len=1;//池化层数

int datasize=0;



std::mt19937 mt_rand(std::chrono::system_clock::now().time_since_epoch().count());

const unsigned int INF=-1;

double rnd(){return (double)mt_rand()/INF;}

tensor<double> random_w(size_s F)
{
    tensor<double> now(F);int sz=now.size();
    for(int i=0;i<now.size();i++) now[i]=(up-down)*rnd()+down;
    return now;
}

std::vector<tensor<double> > random_W(size_s F,int len)
{
    std::vector<tensor<double> > W;
    for(int i=0;i<len;i++) W.push_back(random_w(F));
    return W;
}

tensor<bool> random_d(size_s F)
{
    tensor<bool> now(F);int sz=now.size();
    return now;
}