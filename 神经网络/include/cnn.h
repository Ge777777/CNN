#pragma once
#include"tensor.h"
#include"pool_layer.h"
#include"relu_layer.h"
#include"conv_layer.h"
#include"dropout_layer.h"
#include"tensor.h"
#include"train.h"
#include"softmax_layer.h"

class CNN
{
public:
    void  add_conv_layer(size_s F,int stride,int extend_flitter,int len)
    {
        conv_layer *layer=new conv_layer(F,stride,extend_flitter,len);
        layers.push_back((layer_base *)layer);
    }
    
    void add_pool_layer(size_s F,int stride,int extend_flitter)
    {
        pool_layer *layer=new pool_layer(F,stride,extend_flitter);
        layers.push_back((layer_base *)layer);
    }

    void add_dropout_layer(size_s F,size_s W)
    {
        dropout_layer *layer=new dropout_layer(F,W);
        layer->dropout_set();
        layers.push_back((layer_base *)layer);
    }

    void add_relu_layer(size_s F,int type)
    {
        relu_layer *layer=new relu_layer(F,type);
        layers.push_back((layer_base *)layer);
    }

    void add_softmax_layer(size_s F)
    {
        softmax_layer *layer=new softmax_layer(F);
        layers.push_back((layer_base *)layer);
    }

    size_s& output_size(){return layers.back()->output_.Lim;}

    int getans()
    {
        int ans=0;
        layer_base* last=layers.back();
        for(int i=0;i<10;i++) if(last->output_(i,0,0)>last->output_(ans,0,0)) ans=i;
        return ans;
    }

    void forward(tensor<double> &input)
    {
        tensor<double> now=input;
        int sz=layers.size();
        for(int i=0;i<sz;i++) layers[i]->activate(now),now=layers[i]->output_;
    }

    tensor<double> forwordans(){return layers.back()->output_;}

    void backward(tensor<double> &data,tensor<double> &dataout)
    {
        forward(data);
        tensor<double> delta=layers.back()->output_-dataout;
        int sz=layers.size();
        for(int i=sz-1;i>=0;i--) layers[i]->Deriv_calc(i+1<sz?layers[i+1]->deriv_:delta);
        for(int i=0;i<sz;i++) layers[i]->fix_weight();
    }

    tensor<double> out(){return layers.back()->output_;}

    ~CNN(){for(auto t:layers) delete(t);}

private:
    std::vector<layer_base *> layers;
};