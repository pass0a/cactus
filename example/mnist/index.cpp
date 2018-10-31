#include "mnist.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    mnist_data *data;
    unsigned int cnt;
    int ret;

    if (ret = mnist_load("train-images-idx3-ubyte", "train-labels-idx1-ubyte", &data, &cnt)) {
        printf("An error occured: %d\n", ret);
    }
    else {
        printf("image count: %d\n", cnt);

        free(data);
    }

    return 0;
}