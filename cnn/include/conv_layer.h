#pragma once

#include"layer_base.h"
#include<vector>
#include"train.h"

class conv_layer: public layer_base
{
public:
    int stride_;
    int extend_flitter_;
    std::vector<tensor<double> > W_;

    conv_layer(size_s F,int stride,int extend_flitter,int len): layer_base(F,(F-extend_flitter)/stride+1)
    {
        stride_=stride;extend_flitter_=extend_flitter;
        W_=random_W(F,len);
    }

    void activate(tensor<double>& input) override
    {
//        std::cout << "conv_layer activate" << std::endl;
        this->input_=input;
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
        int x=input_.Lim.x,y=input_.Lim.y,z=input_.Lim.z;
        int xx=output_.Lim.x,yy=output_.Lim.y;
        for(int k=0;k<z;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        {
            int aa=i*stride_,bb=j*stride_;
            double sum=0;int sz=W_.size();
            for(int op=0;op<sz;op++)
            for(int a=aa;a<aa+extend_flitter_;a++)
            for(int b=bb;b<bb+extend_flitter_;b++) W_[op](a-aa,b-bb,k)-=deriv_(a,b,k)*rate;
        }
    }

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        memset(deriv_.data,0,sizeof(deriv_.data));
        int x=input_.Lim.x,y=input_.Lim.y,z=input_.Lim.z;
        int xx=output_.Lim.x,yy=output_.Lim.y;
        for(int k=0;k<z;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        {
            int aa=i*stride_,bb=j*stride_;
            double sum=0;int sz=W_.size();
            for(int op=0;op<sz;op++)
            for(int a=aa;a<aa+extend_flitter_;a++)
            for(int b=bb;b<bb+extend_flitter_;b++) deriv_(a,b,k)+=W_[op](a-aa,b-bb,k);
        }
    }
    ~conv_layer() = default;
};