#include"cnn.h"

int main()
{
    CNN cnn;
    cnn.add_conv_layer({28,28,1},1,3,3);
}