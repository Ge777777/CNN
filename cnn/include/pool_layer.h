#pragma once

#include"layer_base.h"

const double inf=1e9;


class pool_layer: public layer_base
{
public:
    int stride_;
    int extend_flitter_;
    pool_layer(size_s F,int stride,int extend_flitter):layer_base(F,((F-extend_flitter)/stride)+1) {stride_=stride,extend_flitter_=extend_flitter;}
    #define debug std::cerr<<maxx<<std::endl
    void activate(tensor<double>& input) override
    {
        this->input_=input.clone();
        tensor<double> now(input.Lim);
        int x=input.Lim.x,y=input.Lim.y,z=input.Lim.z;
        int xx=output_.Lim.x,yy=output_.Lim.y;
        for(int k=0;k<z;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        {
            int aa=i*stride_,bb=j*stride_;
            double maxx=-10000;
            for(int a=aa;a<aa+extend_flitter_;a++)
            for(int b=bb;b<bb+extend_flitter_;b++) maxx=max(maxx,input_(a,b,k));
            output_(i,j,k)=maxx;
        }
    }
    #undef debug
    
    void fix_weight() override {}

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        int xx=output_.Lim.x,yy=output_.Lim.y;
        for(int z=0;z<input_.Lim.z;z++)
        for(int x=0;x<input_.Lim.x;x++)
        for(int y=0;y<input_.Lim.y;y++)
        {
            double sum=0;
            int l=x/stride_,l2=y/stride_;
            int r=(x-extend_flitter_-1)/stride_,r2=(y-extend_flitter_-1)/stride_;
            for(int i=l;i<r;i++)
            for(int j=l2;j<r2;j++) if(output_(i,j,z)==input_(x,y,z)) sum+=prev_delta(i,j,z);

            deriv_(x,y,z)=sum;
        }
    }
    ~pool_layer() = default;
};