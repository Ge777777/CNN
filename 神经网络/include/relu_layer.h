#pragma once

#include"layer_base.h"

using namespace std;

class relu_layer: public layer_base
{
public:
    relu_layer(size_s F,int type):layer_base(F,F){type_=type;}
    void activate(tensor<double> &input) override
    {
        this->input_=input;
        for(int i=0;i<input.Lim.x;i++)
        for(int j=0;j<input.Lim.y;j++)
        for(int k=0;k<input.Lim.z;k++) output_(i,j,k) = input(i,j,k)<0?0:input(i,j,k);
        if(type_==1) output_.Lim.x*=output_.Lim.y,output_.Lim.y=1;
    }

    void fix_weight() override{}

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        for(int i=0;i<input_.Lim.x;i++)
        for(int j=0;j<input_.Lim.y;j++)
        for(int k=0;k<input_.Lim.z;k++) deriv_(i,j,k) = prev_delta(i,j,k)<0?0:prev_delta(i,j,k);
    }
private:
    int type_;
};