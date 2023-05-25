#include"../include/cnn.h"
#include"../include/read_csv.h"

int main() {
    CNN cnn;
    for (int i = 0; i < extend_flitter_layerlen; i++)
        cnn.add_conv_layer({basic_x, basic_y, baisc_z}, extend_flitter_stride, extend_flitter_size, extend_flitter_len);
    cnn.add_relu_layer(cnn.output_size(), 0);
    cnn.add_pool_layer(cnn.output_size(), pool_extend_flitter_stride, pool_extend_flitter_size);
    cnn.add_relu_layer(cnn.output_size(), 1);

    for (int i = 0; i < dropout_layerlen; i++) {
        size_s F = cnn.output_size(), W = F;
        W.x--;
        cnn.add_dropout_layer(F, W);
    }
    cnn.add_relu_layer(cnn.output_size(), 0);
    cnn.add_softmax_layer(cnn.output_size());
    cnn.add_softmax_layer(cnn.output_size());

    std::vector<IOData> T = read_csv();

    //输出 T
    for (auto &t: T) {
        for (int i = 0; i <= 28 * 28 - 1; i++)
            printf("%.0lf ", t.grayPixels[i]);
        printf("\n");
    }


    for (auto &t: T) cnn.backward(t.grayPixels, t.outputVector);
    T = read_csv();
    int cnt = 0, acnum = 0;
    for (auto &t: T) {
        cnn.forward(t.grayPixels);
        tensor<double> ans = cnn.out();
        int ansid = cnn.getans();
        if (ans(ansid, 0, 0) > 0.5) acnum++;
        cnt++;
    }
    printf("%.5lf\n", 1.0 * acnum / cnt);
}