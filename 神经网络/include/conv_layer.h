#pragma once

#include"layer_base.h"
#include<vector>
#include"train.h"

class conv_layer: public layer_base
{
    int stride_;
    int extend_flitter_;
    std::vector<tensor<double> > W_,b_;

    conv_layer(size_s F,int stride,int extend_flitter,std::vector<tensor<double> > W,std::vector<tensor<double> >b): layer_base(F,(F-extend_flitter)/stride+1){W_=W,b_=b;}

    void activate(const tensor<double> &input)
    {
        this->input_=input;
        tensor<double> now(input.Lim);
        int x=input.Lim.x,y=input.Lim.y,z=input.Lim.z;
        int xx=output_.Lim.x,yy=output_.Lim.y;
        for(int k=0;k<z;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        {
            int aa=i*stride_,bb=j*stride_;
            double sum=0;int sz=W_.size();
            for(int op=0;op<sz;op++)
            for(int a=aa;a<aa+extend_flitter_;a++)
            for(int b=bb;b<bb+extend_flitter_;b++) sum+=input_(a,b,k)*W_[op](a-aa,b-bb,k);
            output_(i,j,k)=sum;
        }
    }

    void fix_weight() override
    {
        int sz=deriv_.size();
        int z=input_.Lim.z,x=extend_flitter_,y=extend_flitter_;
        for(int op=0;op<sz;op++)
        for(int k=0;k<z;k++)
        for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
        {
            
        }
    }

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        
    }
};