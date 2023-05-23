#pragma once

#include"layer_base.h"
#include<cmath>

class softmax_layer: public layer_base
{
public:
    softmax_layer(size_s F):layer_base(F,F){}
    void activate(tensor<double> &input) override
    {
        this->input_=input;int sz=input.size();
        for(int i=0;i<sz;i++) output_[i]=1.0/(1+exp(-input[i]));
    }

    double deriv(double x)
    {
        double sig=1.0/(1.0+exp(-x));
        return sig*(1-sig);
    }
    
    void fix_weight() override {}

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        int sz=input_.size();
        for(int i=0;i<sz;i++) deriv_[i]=prev_delta[i]*deriv(input_[i]);
    }
};