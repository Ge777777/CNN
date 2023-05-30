//
// Created by 77 on 2023/5/29.
//

#ifndef CNN_SHAP_H
#define CNN_SHAP_H
#include"layer_base.h"
class shape_layer:public layer_base{
public:
    size_s input_shape;
    shape_layer(size_s F): layer_base(F,{F.x*F.y,1,F.z}){}
    void activate(tensor<double>& input) override
    {
        input_shape=input.Lim;
        int sz=input.size();
        for(int i=0;i<sz;i++) output_[i]=input[i];
    }
    void fix_weight() override{}
    void Deriv_calc(tensor<double> &prev_delta) override
    {
        deriv_=prev_delta.clone();
        deriv_.Lim=input_shape;
    }
};
#endif //CNN_SHAP_H
