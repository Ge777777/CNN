#include"../include/cnn.h"
#include"../include/read_csv.h"

int wa[15];
int main()
{
    CNN cnn;
    cnn.add_conv_layer({basic_x,basic_y,baisc_z},extend_flitter_stride,extend_flitter_size,extend_flitter_len);
    cnn.add_relu_layer(cnn.output_size());
    cnn.add_pool_layer(cnn.output_size(),pool_extend_flitter_stride,pool_extend_flitter_size);
    cnn.add_shape_layer(cnn.output_size());
    size_s F=cnn.output_size(),W=F;
    W.x=100;
    cnn.add_dropout_layer(F,W);
    cnn.add_relu_layer(cnn.output_size());
    F=cnn.output_size(),W=F;
    W.x=10;
    cnn.add_dropout_layer(F,W);
    cnn.add_relu_layer(cnn.output_size());
    cnn.add_softmax_layer(cnn.output_size());
    std::vector<case_s> T=read_csv();
    int cnt=0,acnum=0;datasize=T.size();
    for(auto &t:T)
    {
        cnn.backward(t.data,t.dataout);
        int ansid=cnn.getans();
        if(t.dataout[ansid]) acnum++;
        cnt++;
        if(cnt%1000==0) cerr<<(double)acnum/1000<<endl,acnum=0;
    }
    T=read_csv();
    cnt=0,acnum=0;
    for(auto &t:T)
    {
        cnn.forward(t.data);
        int ansid=cnn.getans();
        if(t.dataout[ansid]) acnum++;
        cnt++;
        if(cnt%1000==0) cerr<<(double)acnum/cnt<<endl;
    }
    printf("%.5lf\n",1.0*acnum/cnt);
}