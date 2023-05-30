#pragma once

#include"layer_base.h"
#include<cmath>

class softmax_layer: public layer_base
{
public:
    double sum=0,maxx=0;
    softmax_layer(size_s F):layer_base(F,F){}
    void activate(tensor<double>& input) override
    {
        this->input_=input.clone();int sz=input.size();
        maxx = 0;sum = 0;
        for(int i=0;i<sz;i++) maxx=max(maxx,input_[i]);
        for(int i=0;i<sz;i++) sum+=exp(input_[i]-maxx);
        for(int i=0;i<sz;i++) output_[i]=exp(input_[i]-maxx)/sum;
    }


    
    void fix_weight() override {}

    double deriv_calc(int x,int y)
    {
        if(x==y) return output_[x]*(1-output_[x]);
        else return -output_[x]*output_[y];
    }

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        deriv_=prev_delta.clone();
    }
};