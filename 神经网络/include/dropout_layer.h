#pragma once

#include"layer_base.h"
#include"train.h"

class dropout_layer: public layer_base
{
    tensor<double> W_,b_;
    
    dropout_layer(size_s F):layer_base({F.x*F.y*F.z,1,1},{F.x*F.y*F.z,1,1})
    {
        int sz=F.x*F.y;
        size_s N={sz,sz,F.z},M={sz,1,F.z};
        W_=random_w(N);b_=random_w(M);
    }

    void dropout_set()
    {
        int sz=W_.size();
        int num=del_edge_num;
        while(num--)
        {
            int x=mt_rand()%sz;
            W_[x]=0;
        }
    }

    double activate_function(double v){return v>0?v:0;}

    void activate(tensor<double> &input) override
    {
        this->input_=input;
        output_=W_*input+b_;
    }

    void fix_weight() override
    {
        int sz=b_.Lim.x,zz=b_.Lim.z;
        for(int i=0;i<sz*zz;i++) b_[i]=(b_[i]-deriv_[i]*rate);
        for(int k=0;k<zz;k++)
        for(int i=0;i<sz;i++)
        for(int j=0;j<sz;j++) W_(i,j,k)=W_(i,j,k)-rate*input_(j,0,k)*deriv_(i,0,k);
    }

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        deriv_=W_.transpose()*prev_delta;
    }
};