#pragma once

#include"layer_base.h"
#include"train.h"

class dropout_layer: public layer_base
{
public:
    tensor<double> W_;
    tensor<double> b_;
    
    dropout_layer(size_s F,size_s W): layer_base(F,W)
    {
        int sz=F.x*F.y,sz2=W.x*W.y;
        size_s N={sz2,sz,F.z},M={sz2,1,F.z};
        W_=random_w(N);b_=random_w(M);
    }

    void dropout_set(int num)
    {
        int sz=W_.size();
        while(num--)
        {
            int x=mt_rand()%sz;
            W_.data[x]=0;
        }
    }

    double activate_function(double v){return v>0?v:0;}

    void activate(tensor<double> &input) override
    {
        this->input_=input;
        output_=((W_) * input)+(b_);
    }

    void fix_weight() override
    {
        int xx=W_.Lim.x,yy=W_.Lim.y,zz=b_.Lim.z;
        for(int k=0;k<zz;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++) W_(i,j,k)=W_(i,j,k)-rate*input_(j,0,k)*deriv_(i,0,k);
        for(int k=0;k<zz;k++)
        for(int i=0;i<xx;i++) b_(i,0,k)-=rate*deriv_(i,0,k);
    }

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        int xx=W_.Lim.x,yy=W_.Lim.y,zz=b_.Lim.z;
        for(int i=0;i<xx*zz;i++) b_.data[i]=(b_.data[i]-prev_delta[i]*rate);
        deriv_=W_.transpose()*prev_delta;
    }

    ~dropout_layer(){}
};