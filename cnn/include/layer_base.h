
#pragma once

#include"tensor.h"

double max(double a,double b){return a>b?a:b;}

class layer_base
{

public:
   
   tensor<double> input_,output_;

   tensor<double> deriv_;//dW=db即两者偏导相同，所以只需开一个就好

   layer_base(size_s in_size,size_s out_size):
   input_( in_size),
   output_(out_size),
   deriv_(in_size)
   {}
   virtual ~layer_base(){}
   virtual void activate(tensor<double>& input)=0;
   virtual void fix_weight()=0;
   virtual void Deriv_calc(tensor<double> &prev_delta)=0;
};