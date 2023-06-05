#pragma once

#include"layer_base.h"
#include"train.h"

int totnum=0;
class dropout_layer: public layer_base
{
public:
    tensor<double> W_;
    tensor<double> b_;
    tensor<bool> del;
    dropout_layer(size_s F,size_s W): layer_base(F,W)
    {
        int sz=F.x*F.y,sz2=W.x*W.y;
        size_s N={sz2,sz,F.z},M={sz2,1,F.z};
        W_=random_w(N);b_=random_w(M);
        del=random_d(N);
        for(int i=0;i<sz2*F.z;i++) b_[i]*=10;
    }

    void dropout_set()
    {
        int sz=W_.size();int cutedge_num=sz*cutrate;
        while(cutedge_num--)
        {
            int x=mt_rand()%sz;
            W_.data[x]=0;del.data[x]=1;
        }
    }


    void activate(tensor<double>& input) override
    {
//        std::cout << "dropout_layer activate" << std::endl;
        this->input_ = input.clone();
        output_=((W_) * input)+(b_);
    }

    void fix_weight() override{}

    void Deriv_calc(tensor<double> &prev_delta) override
    {
        int xx=W_.Lim.x,yy=W_.Lim.y,zz=b_.Lim.z;
        deriv_=W_.transpose()*prev_delta;
        for(int i=0;i<xx*zz;i++) b_[i]-=prev_delta[i]*rate;
        for(int k=0;k<zz;k++)
        for(int i=0;i<xx;i++)
        for(int j=0;j<yy;j++)
        {
            if(!del(i,j,k)) W_(i,j,k)-=rate*input_(j,0,k)*prev_delta(i,0,k);
        }
    }

    ~dropout_layer() = default;
};