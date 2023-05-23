#pragma once

#include"tensor.h"
#include<vector>
#include<chrono>
#include<random>
#include<string.h>

const double rate = 0.01;//学习速率

const double up=100,down=-100;//权值初始随机范围

const int basic_x=28,basic_y=28,baisc_z=1; //初始矩阵大小

const int del_edge_num=1000;//dropout随机删边次数

const int extend_flitter_stride=1;//卷积层步幅
const int extend_flitter_size=3;//卷积核大小
const int extend_flitter_len=3;//卷积核数
const int extend_flitter_layerlen=4;//卷积层数

const int pool_extend_flitter_stride=3;//池化步幅
const int pool_extend_flitter_size=5;//池化矩阵大小
const int pool_extend_flitter_len=1;//池化层数

const int dropout_layerlen=26;//dropout层数

const std::string train_path="";//训练数据路径
const std::string test_path="";//测试数据路径

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